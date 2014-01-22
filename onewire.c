#include "defines.h"
#include "onewire.h"
#include "onewire_config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

void onewire_port_init()
{
	ONEWIRE_DDR &= ~((1 << ONEWIRE_MASTER_TX_PIN) | (1 << ONEWIRE_MASTER_RX_PIN));
	ONEWIRE_PORT &= ~((1 << ONEWIRE_MASTER_TX_PIN) | (1 << ONEWIRE_MASTER_RX_PIN));
}

void onewire_init()
{
	ONEWIRE_TIMER_INIT; 
	onewire_port_init();
}

// Инициализирует передачу. Возвращает 1, если устройства ответили.
char onewire_write_reset()
{
	onewire_port_init();
	int i;
	ONEWIRE_DDR |= 1<<ONEWIRE_MASTER_TX_PIN;
	for (i = 0; i < 5; i++)
	{	
		ONEWIRE_WAIT(100);
	}
	ONEWIRE_DDR &= ~(1<<ONEWIRE_MASTER_TX_PIN);

	int res = 0;
	for (i = 0; i < 500; i++)
	{
		if (ONEWIRE_MASTER_RX) res = 1;
		ONEWIRE_WAIT(1);
	}	
	return res;
}

// Читает 1 бит
char onewire_read_bit()
{	onewire_port_init();
	ONEWIRE_MASTER_TX(5); ONEWIRE_WAIT(5);
	char cbit = 1;
	ONEWIRE_TIMER_REG = 0;
	int t = 0;
	while (t < 1)
	{
		if (ONEWIRE_MASTER_RX) cbit = 0;
		if (ONEWIRE_TIMER_REG > 100 * ONEWIRE_USEC)
		{
			t++;
			ONEWIRE_TIMER_REG = 0;
		}
	}
	return cbit;
}

// Читает байт
unsigned char onewire_read_byte()
{
	unsigned char res, bit, cbit;
	res = 0;
	for (bit = 0; bit < 8; bit++)
	{		
		cbit = onewire_read_bit();
		if (cbit)
			res |= (1 << bit);
	}
	return res;
}

void onewire_write_bit(unsigned char b)
{
	onewire_port_init();
	if (b) { ONEWIRE_WRITE1; } else { ONEWIRE_WRITE0;}
}

void onewire_write_byte(unsigned char b)
{
	unsigned char bit;
	for (bit = 0; bit < 8; bit++)
	{
		onewire_write_bit((b >> bit) & 1);
	}
}

// Считает CRC
char onewire_check_crc(unsigned char* data, unsigned char size)
{
    uint8_t crc=0;
    uint8_t i,j;
    for (i=0; i<size;i++) 
    {
		uint8_t inbyte = data[i];
        for (j=0;j<8;j++) 
		{
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
            if (mix) 
            crc ^= 0x8C;                  
			inbyte >>= 1;
        }
    }
    return crc;
}


// В буфере только нули?
char onewire_all_zeros(unsigned char* data, unsigned char size)
{
    uint8_t i;
    for (i=0; i<size;i++) 
    {
		if (data[i]) return 0;
    }
	return 1;
}

#ifdef ONEWIRE_SEARCH_SUPPORT
// Поиск устройств, num - битовая маска, по которой идёт ветвление, out - указатель на 8 байт
// возвращает кол-во пройденных ветвений
int onewire_search(unsigned int num, unsigned char* out)
{
	char res = onewire_write_reset();
	if (!res) return -1;
	
	onewire_write_byte(ONEWIRE_COMMAND_SEARCH);
	int byte, bit, rbit;
	int conflicts = 0;
	for (byte = 0; byte < 8; byte++)
	{
		out[byte] = 0;
		for (bit = 0; bit < 8; bit++)
		{
			char bit1 = onewire_read_bit();
			char bit2 = onewire_read_bit();
			rbit = 0;
			if (bit1 && !bit2)
			{
				rbit = 1;
			}
			else if (!bit1 && !bit2)
			{
				rbit = (num >> conflicts) & 1;
				conflicts++;
			} else if (!bit1 && bit2)
			{
				rbit = 0;
			}
			if (rbit)
				out[byte] |= 1 << bit;
			onewire_write_bit(rbit);
		}
	}
	
	return conflicts;
}

// Итерация поиска
void onewire_search_iter(int num, int depth, void (*f)(unsigned char* out))
{
	unsigned char serial[8];
	int conflicts = onewire_search(num, serial);	
	if (conflicts < 0) return;	
	if ((onewire_check_crc(serial, 8) == 0) && !onewire_all_zeros(serial, 8))
		f(serial);
		
	int d;
	for (d = depth+1; d < conflicts; d++)
		onewire_search_iter(num | (1UL << d), d, f); // углубляемся. 
}

// Ищет все устройства. f - указатель к функции, которая вызывается для каждого устройства, out - указатель на 8 байт адреса, включая тип и CRC
void onewire_search_all(void (*f)(unsigned char* out))
{
	onewire_search_iter(0, -1, f);
}
#endif

// Включает мощную подтяжку к VCC
void onewire_pullup()
{
	if (ONEWIRE_MASTER_RX) return;
	ONEWIRE_PORT |= (1<<ONEWIRE_MASTER_TX_PIN) | (1<<ONEWIRE_MASTER_RX_PIN); ONEWIRE_DDR |= (1<<ONEWIRE_MASTER_TX_PIN) | (1<<ONEWIRE_MASTER_RX_PIN);
}
