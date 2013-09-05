#include <avr/io.h>
#include "defines.h"
#include "ibutton.h"
#include "bits.h"
#include "cyfral.h"
#include "onewire.h"

inline void cyfral_send_nibble(uint8_t data)
{
	uint8_t b;
	for (b = 0; b < 4; b++)
	{
		if (data & (1UL<<b))
		{
			ONEWIRE_MASTER_TX(105);			
			ONEWIRE_WAIT(36);
		} else {
			ONEWIRE_MASTER_TX(53);			
			ONEWIRE_WAIT(80);
		}
	}
}

void cyfral_send(uint16_t key)
{
	cyfral_send_nibble(0b0111);
	uint8_t b;
	for (b = 0; b < 8; b++)
	{
		speedup_leds();
		update_leds();
		cyfral_send_nibble(1UL << ((key >> (b*2)) & 0b11));
	}
}

long int read_cyfral()
{
	uint16_t buffer[100];
	int pos = 0;
	do 
	{
		TCNT1 = 0;
		while (!CYFRAL_SIGNAL && TCNT1 < 0x400);
		if (TCNT1 >= 0x400) return -1;
		//buffer[pos++] = TCNT1;
		TCNT1 = 0;
		while (CYFRAL_SIGNAL && TCNT1 < 0x400);
		if (TCNT1 >= 0x400) return -1;
		buffer[pos++] = TCNT1;
		
	} while (pos < sizeof(buffer)/2);
	int i, j;
	int startpos = -1;
	for (i = 0; i < pos-9*4; i++)
	{
		if ((buffer[i] > 70) && (buffer[i+1] > 70)  && (buffer[i+2] > 70) && (buffer[i+3] < 70))
		{
			startpos = i;
			break;
		}
	}
	uint16_t code = 0;
	int b = 0;
	if (startpos >= 0)
	{
		for (i = startpos+4; i < startpos+9*4; i+=4)
		{
			for (j = 0; j < 4; j++)
			{
				//send_num(buffer[i+j]);
				if (buffer[i+j] > 70)
					code |= j << (b*2);
			}
			b++;
		}
	} else return -1;
	return code;	
}

long int read_cyfral_with_check()	
{
	long int code = 0, tries = 0, i;
	for (i = 0; i < 10; i++)
	{
		long int code2 = read_cyfral();
		if ((code2 >= 0) && (code == code2))
		{
			tries++;
		} else {
			tries = 0;
			code = code2;
		}
		if (tries >= 3) 
		{
			return code2;
		}
	}	
	return -1;
}

