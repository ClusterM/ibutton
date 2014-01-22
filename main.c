#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include "ibutton.h"
#include "bits.h"
#include "onewire.h"
#include "cyfral.h"
#include "metacom.h"
#include "usb.h"

// Некоторые универсальные ключи
unsigned char VEZDEHOD_KEY1[] PROGMEM = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3D};
unsigned char VEZDEHOD_KEY2[] PROGMEM = {0x01, 0xBE, 0x40, 0x11, 0x5A, 0x36, 0x00, 0xE1};
unsigned char VEZDEHOD_KEY3[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x2F};
unsigned char VEZDEHOD_KEY4[] PROGMEM = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char VEZDEHOD_KEY5[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x9B};
unsigned char VEZDEHOD_KEY6[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x1A};
unsigned char VEZDEHOD_KEY7[] PROGMEM = {0xFF, 0xFF, 0xFF};
unsigned char VEZDEHOD_KEY8[] PROGMEM = {0xFF, 0x00, 0x00};
/*
unsigned char VEZDEHOD_KEY9[] PROGMEM = {0x01, 0xBE, 0x40, 0x11, 0x0A, 0x00, 0x00, 0x1D};
unsigned char VEZDEHOD_KEY10[] PROGMEM = {0x01, 0x05, 0xE7, 0x56, 0x0B, 0x00, 0x00, 0x4D};
unsigned char VEZDEHOD_KEY11[] PROGMEM = {0x01, 0x48, 0x7A, 0x44, 0x0D, 0x00, 0x00, 0xC7};
unsigned char VEZDEHOD_KEY12[] PROGMEM = {0x01, 0x87, 0x26, 0x87, 0x0B, 0x00, 0x00, 0xA8};
unsigned char VEZDEHOD_KEY13[] PROGMEM = {0x01, 0x46, 0x81, 0x57, 0x0B, 0x00, 0x00, 0x63};
unsigned char VEZDEHOD_KEY14[] PROGMEM = {0x01, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x2D};
unsigned char VEZDEHOD_KEY15[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x14};
unsigned char VEZDEHOD_KEY16[] PROGMEM = {0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xB2};
unsigned char VEZDEHOD_KEY17[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x74};
unsigned char VEZDEHOD_KEY18[] PROGMEM = {0x01, 0x4C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x71};
unsigned char VEZDEHOD_KEY19[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x49};
unsigned char VEZDEHOD_KEY20[] PROGMEM = {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4C, 0xFF};
unsigned char VEZDEHOD_KEY21[] PROGMEM = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x00};
unsigned char VEZDEHOD_KEY22[] PROGMEM = {0x01, 0xF0, 0xD6, 0xBC, 0x0B, 0x00, 0x00, 0xCF};
unsigned char VEZDEHOD_KEY23[] PROGMEM = {0x01, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5D};
unsigned char VEZDEHOD_KEY24[] PROGMEM = {0x01, 0x38, 0x3A, 0x65, 0x0E, 0x00, 0x00, 0xAD};
*/
unsigned char* VEZDEHOD_KEYS[] = {VEZDEHOD_KEY1, VEZDEHOD_KEY2, VEZDEHOD_KEY3, VEZDEHOD_KEY4, VEZDEHOD_KEY5, VEZDEHOD_KEY6, VEZDEHOD_KEY7, VEZDEHOD_KEY8
/*, VEZDEHOD_KEY9, VEZDEHOD_KEY10, VEZDEHOD_KEY11, VEZDEHOD_KEY12, VEZDEHOD_KEY13, VEZDEHOD_KEY14, VEZDEHOD_KEY15, VEZDEHOD_KEY16, VEZDEHOD_KEY17, VEZDEHOD_KEY18, VEZDEHOD_KEY19, VEZDEHOD_KEY20, VEZDEHOD_KEY21, VEZDEHOD_KEY22, VEZDEHOD_KEY23, VEZDEHOD_KEY24
*/};

volatile unsigned char key_count = 0;
unsigned char current_key = 0;
unsigned char leds_mask = 0;
unsigned char vezdehod_mode = 0;
uint16_t leds_time = 0;

#ifdef DEBUG
uint16_t debug_log[128];
uint8_t debug_log_size = 0;
#define WRITE_LOG(t) if (debug_log_size < 128) debug_log[debug_log_size++] = t
#else
#define WRITE_LOG(t) ;
#endif

ISR(INT0_vect)
{
	// Выключаем прерывание после срабатывания
	// Его цель - только вывести устройство из спящего режима
	unset_bit(GICR, INT0);
}

ISR(INT1_vect)
{
	// Выключаем прерывание после срабатывания
	// Его цель - только вывести устройство из спящего режима
	unset_bit(GICR, INT1);
}

// Включает заданные светодиоды по маске
void set_leds(unsigned char leds_mask)
{
	if (leds_mask & (1<<0)) set_bit(LED1_PORT, LED1_PIN); else unset_bit(LED1_PORT, LED1_PIN); // top led
	if (leds_mask & (1<<1)) set_bit(LED2_PORT, LED2_PIN); else unset_bit(LED2_PORT, LED2_PIN); // top-right led
	if (leds_mask & (1<<2)) set_bit(LED3_PORT, LED3_PIN); else unset_bit(LED3_PORT, LED3_PIN); // bottom-right led
	if (leds_mask & (1<<3)) set_bit(LED4_PORT, LED4_PIN); else unset_bit(LED4_PORT, LED4_PIN); // bottom led
	if (leds_mask & (1<<4)) set_bit(LED5_PORT, LED5_PIN); else unset_bit(LED5_PORT, LED5_PIN); // bottom-left led	
	if (leds_mask & (1<<5)) set_bit(LED6_PORT, LED6_PIN); else unset_bit(LED6_PORT, LED6_PIN); // top-left led	
	if (leds_mask & (1<<6)) set_bit(LED7_PORT, LED7_PIN); else unset_bit(LED7_PORT, LED7_PIN); // center led	
}

// Ускоряет мигание светодиодами
void speedup_leds(void)
{
	leds_time+=32;
}

// Зажигаем следующий светодиод, если надо,
// т.е. в каждый момент времени горит только один
void update_leds(void)
{
	leds_time++;
	if ((leds_mask & (1<<7)) && ((leds_time >> 13) % 2 == 1))
		set_leds(0);
	else set_leds(leds_mask & (1UL << (leds_time % 16)));
}

// Зажигаем следующий светодиод, но больше времени уделяем на горение,
// т.е. светодиоды визуально светятся ярче
void update_leds_bright(void)
{
	leds_time++;
	if ((leds_mask & (1<<7)) && ((leds_time >> 13) % 2 == 1))
		set_leds(0);
	else set_leds(leds_mask & (1UL << (leds_time % 8)));
}

// Отображает заданную цифру
void show_digit(unsigned char digit)
{
	unsigned char mask = 0;
	switch (digit&0x0F)
	{
		case 0: mask = 0b00111111; break;
		case 1: mask = 0b00000110; break;
		case 2: mask = 0b01011011; break;
		case 3: mask = 0b01001111; break;
		case 4: mask = 0b01100110; break;
		case 5: mask = 0b01101101; break;
		case 6: mask = 0b01111101; break;
		case 7: mask = 0b00000111; break;
		case 8: mask = 0b01111111; break;
		case 9: mask = 0b01101111; break;
		case 0xA: mask = 0b01110111; break;
		case 0xB: mask = 0b01111100; break;
		case 0xC: mask = 0b00111001; break;
		case 0xD: mask = 0b01011110; break;
		case 0xE: mask = 0b01111001; break;
		case 0xF: mask = 0b01110001; break;
		default: mask = 0; break;
	}
	if (digit >> 4) mask |= (1<<7);
	leds_mask = mask;
	set_leds(mask);
}

// Проверяет, есть ли заданный ключ в базе
int key_exists(unsigned char* new_key)
{
	unsigned char i, i2, bingo;
	unsigned char old_key[8];
	for (i = 0; i < key_count; i++)
	{
		bingo = 1;
		eeprom_read_block(old_key, (void*)((i+1)*8), 8);
		for (i2 = 0; i2 < 8; i2++) if (new_key[i2] != old_key[i2]) bingo = 0;
		if (bingo) return i+1;
	}
	return 0;
}

// Считывает ключ
int read_mode()
{
	onewire_init();

	int t = 0;
	unsigned char serial[8];
	char read_ok = 0;

	leds_mask = 1<<6; // Во время считывания мигаем средним светодиодом
	while (BUTTON_PRESSED)
	{
		wdt_reset();
		update_leds();
		_delay_ms(1);
	}

	while (1)
	{
		wdt_reset();
		update_leds();
		char res = onewire_write_reset(); // Посылает 1-wire ресет
		if (res) // Если устройство ответило...
		{
			// Посылаем команду считывания ключа
			onewire_write_byte(ONEWIRE_COMMAND_READ_ROM);
			int b;
			// Читаем 8 байт из ключа
			for (b = 0; b < 8; b++)
				serial[b] = onewire_read_byte();						
			// Проверяем CRC
			if ((onewire_check_crc(serial, 8) == 0) && !onewire_all_zeros(serial, 8))
			{
				read_ok = 1;
			}
		}
		
		// Теперь пытаемся прочитать цифрал-клюс
		CYFRAL_PULLUP_ENABLE;  // подтяжка 750 Ом
		CYFRAL_REFERENCE_ENABLE; // делитель напряженния
		// Читаем ключ несколько раз, с проверкой
		long int code = read_cyfral_with_check();
		// Выключаем назад подтяжку и делитель напряжения
		CYFRAL_PULLUP_DISABLE;
		CYFRAL_REFERENCE_DISABLE;
		// Если ключ прочитан успешно...
		if (code >= 0)
		{
			serial[0] = 0xFF;
			serial[1] = code & 0xFF;
			serial[2] = (code>>8) & 0xFF;
			serial[3] = serial[4] = serial[5] = serial[6] = serial[7] = 0;
			read_ok = 1;
		}
		t++;
		// После 2000 неудачных попыток выходим и выключаемся
		if (t > 2000)
			return 0;
		if (BUTTON_PRESSED || USB_POWERED) // При нажатии кнопки или подключения USB...
			return 1; // возврат в основной режим
		
		// Если ключ прочитан успешно...
		if (read_ok)
		{
			read_ok = 0;
			t = 0;

			// Проверяем - нет ли у нас уже такого ключа?
			int exists = key_exists(serial);
			int num;
			// Если нет...
			if (!exists)
			{
				// Сохраняем ключ
				current_key = key_count;
				key_count++;
				eeprom_write_block(serial, (void*)(key_count*8), 8);		
				eeprom_write_byte((void*)0, key_count);
				num = key_count;
			} else 
			{
				// Иначе отображаем номер существующего
				num = exists;
			}
			// Мигаем три раза номером ключа
			for (t = 0; t < 3; t++)
			{
				show_digit(num);
				int i;
				for (i = 0;i < 300; i++)
				{
					wdt_reset();
					update_leds();
					_delay_ms(1);					
				}
				set_leds(0);
				for (i = 0;i < 300; i++)
				{
					wdt_reset();
					_delay_ms(1);					
				}
			}			
			leds_mask = 1<<6;
		}
	}
}

// Читает байт от мастера. Таймаут - возвращает 0, ресет - 1, удачно - 2
int ibutton_read_byte_from_master(unsigned char* value)
{
	int i;
	*value = 0;
	for (i = 0; i < 8; i++) // Ждем команду
	{
		TCNT1 = 0; while (!ONEWIRE_MASTER_RX && (TCNT1 < 30000)); if (TCNT1 >= 30000) return 0;
		TCNT1 = 0; while (ONEWIRE_MASTER_RX && (TCNT1 < 30000));
		if (TCNT1 >= 300) return 1;
		if (TCNT1 < 45) *value |= (1 << i);
	}
	return 2;
}

// Посылает мастуру presence-pulse и ждёт команду
int ibutton_wait_for_master3(unsigned char* key)
{
	wdt_reset(); 
	set_leds(0);	// Гасим светодиоды, т.к. нет времени ими мигать
	ONEWIRE_WAIT(20) // Немножко ждём
	ONEWIRE_MASTER_TX(140); // Presence-pulse 
	// Ждём возобновления линии
	TCNT1 = 0; while (ONEWIRE_MASTER_RX && (TCNT1 < 30000));
	if (TCNT1 >= 300) return 1; // Если линия долго прижата мастером, это ресет
	int i, bit;
	unsigned char command = 0;
	i = ibutton_read_byte_from_master(&command); // Получаем комманду
	if (i != 2) return i;
	WRITE_LOG(command);

	if (command == ONEWIRE_COMMAND_SKIP_ROM) // Если нам сначала прислали SKIP_ROM команду. На практике такого не бывало.
	{
		i = ibutton_read_byte_from_master(&command);
		if (i != 2) return i;
		WRITE_LOG(command);
	}

	if ((command == ONEWIRE_COMMAND_READ_ROM) || (command == ONEWIRE_COMMAND_READ_ROM_ALT)) // Получили запрос, шлём ключ
	{
		for (i = 0; i < 8; i++)
		{
			for (bit = 0; bit < 8; bit++)
			{
				// Ждём запроса от мастера
				TCNT1 = 0; while ((!ONEWIRE_MASTER_RX) && (TCNT1 < 30000)); if (TCNT1 >= 30000) return 0;
				// Если нужно передать логический ноль, прижимаем линию
				if (((key[i] >> bit) & 1) == 0) 
				{
					ONEWIRE_MASTER_TX(35);
				}
				// Ждём возобновления линии
				TCNT1 = 0; while (ONEWIRE_MASTER_RX && (TCNT1 < 30000));
				if (TCNT1 >= 300) return 1; // Если линия долго прижата мастером, это ресет
			}
		}
	} 
	
	if (command == ONEWIRE_COMMAND_SEARCH) // Мастер выполняет поиск!
	{
		for (i = 0; i < 8; i++)
		{
			for (bit = 0; bit < 8; bit++)
			{
				char d = (key[i] >> bit) & 1; // Текущий бит
				// Ждём запроса от мастера
				TCNT1 = 0; while ((!ONEWIRE_MASTER_RX) && (TCNT1 < 30000)); if (TCNT1 >= 30000) return 0;
				if (d == 0) // Если нужно передать логический ноль, прижимаем линию
				{
					ONEWIRE_MASTER_TX(35);
				}
				// Ждём возобновления линии
				TCNT1 = 0; while (ONEWIRE_MASTER_RX && (TCNT1 < 30000));
				if (TCNT1 >= 300) return 1; // Если линия долго прижата мастером, это ресет
				
				// Ждём запроса от мастера
				TCNT1 = 0; while ((!ONEWIRE_MASTER_RX) && (TCNT1 < 30000)); if (TCNT1 >= 30000) return 0;
				if (d != 0) // Если нужно передать логическую единицу, прижимаем линию
				{
					ONEWIRE_MASTER_TX(35);
				}
				// Ждём возобновления линии
				TCNT1 = 0; while (ONEWIRE_MASTER_RX && (TCNT1 < 30000));
				if (TCNT1 >= 300) return 1; // Если линия долго прижата мастером, это ресет
				
				// Ждём сигнала от мастера
				TCNT1 = 0; while (!ONEWIRE_MASTER_RX && (TCNT1 < 30000)); if (TCNT1 >= 30000) return 0;
				// Ждём возобновления линии
				TCNT1 = 0; while (ONEWIRE_MASTER_RX && (TCNT1 < 30000));
				if (TCNT1 >= 300) return 1; // Если линия долго прижата мастером, это ресет
				char d2;
				if (TCNT1 < 45) d2 = 1; else d2 = 0; // Бит, который подтверждает мастер
				if (d != d2) return 0; // Если они не совпадают, выходим
			}
		}
	} 
	return 0;
}

// Отвечает на ресет мастеру
void ibutton_wait_for_master2(unsigned char* key)
{
	int reset;
	do
	{
		reset = ibutton_wait_for_master3(key);	
	} while (reset); // Если в результате общения получили ресет, то начинаем общение заново
}

// Ждём ресета от мастера
void ibutton_wait_for_master(unsigned char* key)
{
	int waittime;
	for (waittime = 0; waittime < 100; waittime++)
	{		
		wdt_reset();
		TCNT1 = 0;
		while (!ONEWIRE_MASTER_RX && (TCNT1 < 30000)) // Пока нет сигнала
		{
			wdt_reset();
			update_leds();
			if (BUTTON_PRESSED || USB_POWERED) return;
		};
		// Если долго не было сигнала, ждём дальше
		if (TCNT1 >= 30000) continue;
		// Если же сигнал есть, считаем время
		TCNT1 = 0;	
		while (ONEWIRE_MASTER_RX) if (TCNT1 > 30000) TCNT1 = 30000; // Пока есть сигнал
		if (TCNT1 > 300) // Не слишком короткий
		{
			ibutton_wait_for_master2(key); // Дверь заговорила, отвечаем
		}
		// Был сигнал, ждём ресета с нуля
		waittime = 0;
	}
	ibutton_wait_for_master2(key); // Не дождались, начинаем сами
}

// Режим посылки ключа
int send_mode()
{	
	// Если ключей нет, сразу переходим в режим чтения ключей
	if (!key_count) return 1;
	int t;
	while (1)
	{
		if (current_key >= key_count) current_key = 0;
		// Показываем номер текущего ключа
		show_digit(current_key+1);
		// Ждём пока кнопку, отпустят
		while (BUTTON_PRESSED)
		{
			wdt_reset();
			update_leds_bright();
			_delay_ms(1);
		}
		unsigned char key[8];
		// В обычном режиме читаем ключ из EEPROM
		if (!vezdehod_mode)
			eeprom_read_block(key, (void*)((current_key+1)*8), 8);
		else
		{ // Если режим вездехода, то читаем ключ из PGM памяти
			int i;
			for (i = 0; i < 8; i++)
				key[i] = pgm_read_byte(&VEZDEHOD_KEYS[current_key][i]);
		}
		// Включаем 1-wire
		onewire_init();
		t = 0;
		while (1)
		{
			if (key[0] == 0xFF) // Цифрал
			{
				// После 1000 попыток выключаемся
				if (t > 1000) return 0;
				wdt_reset();
				speedup_leds();
				update_leds();
				uint16_t cyfral_key = key[1] + key[2]*0x100;
				// Посылаем ключ
				cyfral_send(cyfral_key);
			}
			else if (key[0] == 0xFE) // Метаком
			{
				// После 1000 попыток выключаемся
				if (t > 1000) return 0;
				wdt_reset();
				update_leds();
				// Посылаем ключ
				metacom_send(key+1);
			} else { // iButton
				// После трёх попыток выключаемся
				if (t >= 2) return 0;
				// Переходим в режим переговоров с дверью
				ibutton_wait_for_master(key);
			}					
			
			if (BUTTON_PRESSED)
			{
				t = 0;
				current_key++;				
				if (current_key >= key_count) current_key = 0;
				show_digit(current_key+1);
				while (BUTTON_PRESSED)
				{
					wdt_reset();
					update_leds_bright();
					_delay_ms(1);
					t++;
					if (t >= 1000 && !vezdehod_mode) return 1; // смена режима
				}
				break;
			}
			if (USB_POWERED) return 1;
			t++;
		}
	}	
}

void sleep()
{
	onewire_init();
	set_leds(0);
	UCSRB = 0; // disable USART
	unset_bit(PORTD, 0); unset_bit(PORTD, 1); // Прижимаем USART к земле
	set_bit(DDRD, 0); set_bit(DDRD, 1);

	LINE_DISABLE;
	CYFRAL_PULLUP_DISABLE;
	CYFRAL_REFERENCE_DISABLE;
	
	set_bit(MCUCR, SM1); unset_bit2(MCUCR, SM0, SM2); // Power-down спящий режим
	set_bit2(GICR, INT1, INT0); // Включаем прерывания

	set_bit(WDTCR, WDCE), unset_bit(WDTCR, WDE); // Собаку выключаем
	
	if (BUTTON_PRESSED || USB_POWERED) return;
	sleep_mode();
}

int main (void)
{
	UCSRB = 0; // Выключаем UART, из-за него ток утекает, куда не надо

	set_bit(LED1_DDR, LED1_PIN); // top led
	set_bit(LED2_DDR, LED2_PIN); // top-right led
	set_bit(LED3_DDR, LED3_PIN); // bottom-right led
	set_bit(LED4_DDR, LED4_PIN); // bottom led
	set_bit(LED5_DDR, LED5_PIN); // bottom-left led	
	set_bit(LED6_DDR, LED6_PIN); // top-left led	
	set_bit(LED7_DDR, LED7_PIN); // center led	
	
	unset_bit(BUTTON_DDR, BUTTON_PIN);	set_bit(BUTTON_OUT, BUTTON_PIN); // Подтяжка кнопки
	unset_bit(USB_DETECT_DDR, USB_DETECT_PIN);	set_bit(USB_DETECT_OUT, USB_DETECT_PIN); // Подтяжка определения USB	
	unset_bit(CYFRAL_PULLUP_DDR, CYFRAL_PULLUP_PIN); unset_bit(CYFRAL_PULLUP_OUT, CYFRAL_PULLUP_PIN); // Подтяжка 750 Ом выключена
	set_bit(CYFRAL_REFERENCE_DDR, CYFRAL_REFERENCE_PIN); unset_bit(CYFRAL_REFERENCE_OUT, CYFRAL_REFERENCE_PIN); // Делитель напряжения выключен
	set_bit(LINE_ENABLE_DDR, LINE_ENABLE_PIN); unset_bit(LINE_ENABLE_OUT, LINE_ENABLE_PIN); // линия выключена
	onewire_init();

	// Лишние ноги прижимаем к земле
	set_bit(DDRC, 4); unset_bit(PORTC, 4);
	set_bit(DDRC, 5); unset_bit(PORTC, 5);
	set_bit(DDRD, 4); unset_bit(PORTD, 4);	
		
	sei();

	int b, i;
/*
	LINE_ENABLE;
	CYFRAL_REFERENCE_ENABLE;
	while(1)
	for(b = 0; b < 10; b++)
	{
		if (CYFRAL_SIGNAL)
			show_digit(1);
		else 
			show_digit(0);
	}
	*/
	
	while (1)
	{
		set_bit(WDTCR, WDCE), set_bit(WDTCR, WDE); // Собака
		set_bit(WDTCR, WDCE), set_bit3(WDTCR, WDP2, WDP1, WDP0); // Неспешащая собака

		int t = 0;
		vezdehod_mode = 0;
		do
		{
			// При включении показываем бегущий по кругу светодиод
			for(b = 0; b < 6; b++)
			{
				//set_leds(1<<b);
				leds_mask = 1<<b;
				for (i = 0;i < 30; i++) // Ждём 30мс, обнуляя собаку и обновляя светодиоды
				{
					wdt_reset();
					update_leds();
					_delay_ms(1);					
				}
			}
			t++;
			if (t == 5) // Если долго держим кнопку, то пишем лог для отладки или переходим в режим вездехода (в зависимости от директивы DEBUG)
			{
				show_digit(0); // Показываем 0
#ifdef DEBUG
				eeprom_write_byte((void*)1, debug_log_size);				
				eeprom_write_block((char*)debug_log, (void*)256, debug_log_size*2);
#endif
				
				debug_log_size = 0; // Обнуляем debug-log
				for (i = 0;i < 500; i++) // Показываем 0 в течении некоторого полусекунды
				{
					wdt_reset();
					update_leds();
					_delay_ms(1);					
				}
				vezdehod_mode = 1; // Включаем режим вездеход-ключей!
				current_key = 0;
/*
				set_leds(0);
				while(1);
*/
				
			}
		} while (BUTTON_PRESSED);

		if (!vezdehod_mode)
			key_count = eeprom_read_byte((void*)0);
		else
			key_count = sizeof(VEZDEHOD_KEYS) / 2;
		
		if (key_count > 63) key_count = 0;
		
		while (1)
		{
			if (USB_POWERED)
			{
				usb_mode();
				break;
			}
			LINE_ENABLE;
			if (send_mode() == 0) break;
			if (read_mode() == 0) break;
		}
		
		if (vezdehod_mode) current_key = 0;
		sleep();
	}

}

