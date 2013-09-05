#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <string.h>
#include "ibutton.h"
#include "bits.h"
#include "usart.h"

const char* COMMAND_NAME = "name";
const char* COMMAND_REBOOT = "reboot";
const char* COMMAND_READ = "read";
const char* COMMAND_ERASE = "erase";
const char* COMMAND_WRITE = "write";


volatile char usart_command[30];
volatile int usart_command_length = 0;
volatile unsigned char usart_params[8];
volatile int usart_params_length = 0;
volatile char usart_mode_params;
volatile char usart_execute = 0;

ISR(USART_RXC_vect)
{
	char b;
	unsigned char c;			
	while (UCSRA & (1<<RXC))
	{
		b = UDR;
		if (b == '\r' || b == '\n')
		{
			usart_command[usart_command_length] = 0;
			usart_execute = 1;
		}
		else if (b == ' ')
		{
			if (!usart_mode_params) 
				usart_params_length = 0;
			usart_mode_params = 1;
		}
		else if (!usart_mode_params)
		{
			if (usart_command_length+1 < sizeof(usart_command))
				usart_command[usart_command_length++] = b;
		}
		else 
		{
			
			if (b >= '0' && b <= '9') c = b-'0';
				else if (b >= 'A' && b <= 'F') c = b-'A'+10;
				else continue;
			if (usart_params_length < 16)
			{
				if (usart_params_length % 2 == 0) usart_params[usart_params_length/2] = (c<<4);
					else usart_params[usart_params_length/2] |= (c & 0x0F);
				usart_params_length++;
			}
		}
	}
}

void usb_mode(void)
{
	int b;
	usart_command_length = 0;
	usart_mode_params = 0;
	usart_execute = 0;
	for (b = 0; b < 8; b++)	
		usart_params[b] = 0;
	unsigned char usb_key_count = eeprom_read_byte((void*)0);
	USART_init();
	while (USB_POWERED)
	{	
		for(b = 0; b < 6; b++)
		{
			wdt_reset();
			set_leds(1<<b);
			_delay_ms(50);
			if (usart_execute)
			{
				if (usart_command_length > 0)
				{
					set_bit(UCSRB, TXEN); // Включаем TX
					_delay_ms(10);
					if (strcmp((char*)usart_command, COMMAND_NAME) == 0)
					{
						USART_TransmitText("iButton Multikey by Cluster\r\n> ");
					}
					else if (strcmp((char*)usart_command, COMMAND_REBOOT) == 0)
					{
						USART_TransmitText("OK.\r\n");
						cli();
						set_bit(WDTCR, WDE);
						while(1);
					}					
					else if (strcmp((char*)usart_command, COMMAND_READ) == 0)
					{
						USART_TransmitText("Count: ");
						USART_TransmitHex(usb_key_count);
						int k;
						for (k = 0; k < usb_key_count; k++)
						{
							USART_TransmitText("\r\nKey: ");
							USART_TransmitHex(k+1);
							USART_TransmitText(" ");
							unsigned char key[8];
							eeprom_read_block(key, (void*)((k+1)*8), 8);
							int b;
							for (b = 0; b < 8; b++)
							{
								USART_TransmitHex(key[b]);
							}
						}
						USART_TransmitText("\r\n> ");
					}					
					else if (strcmp((char*)usart_command, COMMAND_ERASE) == 0)
					{
						usb_key_count = 0;
						eeprom_write_byte((void*)0, usb_key_count);
						USART_TransmitText("Done.\r\n> ");
					}
					else if (strcmp((char*)usart_command, COMMAND_WRITE) == 0)
					{
						
						usb_key_count++;
						eeprom_write_block((char*)usart_params, (void*)(usb_key_count*8), 8);		
						eeprom_write_byte((void*)0, usb_key_count);
						USART_TransmitText("Done.\r\n> ");
					}
					else USART_TransmitText("Unknown command\r\n> ");
					_delay_ms(10);
					unset_bit(UCSRB, TXEN); // Выключаем TX
				}
				usart_command_length = 0;
				usart_mode_params = 0;
				usart_execute = 0;
				for (b = 0; b < 8; b++)	
					usart_params[b] = 0;			
			}
		}
	}
}