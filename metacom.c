#include <avr/io.h>
#include "defines.h"
#include "ibutton.h"
#include "bits.h"
#include "metacom.h"
#include "onewire.h"

inline void metacom_send_byte(uint8_t data)
{
	uint8_t b;
	for (b = 0; b < 8; b++)
	{
		if (data & (1UL<<b))
		{
			ONEWIRE_MASTER_TX_OFF;
			ONEWIRE_WAIT(METACOM_T*2/3); // 1
			ONEWIRE_MASTER_TX_ON;
			ONEWIRE_WAIT(METACOM_T/3);
		} else {
			ONEWIRE_MASTER_TX_OFF;
			ONEWIRE_WAIT(METACOM_T/3); // 0
			ONEWIRE_MASTER_TX_ON;
			ONEWIRE_WAIT(METACOM_T*2/3);
			// Тут не надо отпускать TX перед посылкой следующего пакета
		}
	}
}

void metacom_send(unsigned char* key)
{
	ONEWIRE_MASTER_TX(METACOM_T); // Синхронизирующий бит
	
	ONEWIRE_WAIT(METACOM_T/3); // 0
	ONEWIRE_MASTER_TX(METACOM_T*2/3);

	ONEWIRE_WAIT(METACOM_T*2/3); // 1
	ONEWIRE_MASTER_TX(METACOM_T/3);

	ONEWIRE_WAIT(METACOM_T/3); // 0
	ONEWIRE_MASTER_TX(METACOM_T*2/3);
	
	int b;
	for (b = 0; b < 4; b++)
	{
	/*
		speedup_leds();
		*/
		update_leds();
		metacom_send_byte(key[b]);
	}
}


