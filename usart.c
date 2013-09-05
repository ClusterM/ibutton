#include "defines.h"
#include <avr/io.h>

void USART_init(void)
{
  unsigned int bd = (F_CPU / (16UL * UART_BAUD)) - 1;
  UBRRL = bd & 0xFF;
  UBRRH = bd >> 8;

  UCSRB = /*_BV(TXEN) | */_BV(RXEN) | _BV(RXCIE); /* tx/rx enable */
//  UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;
  UCSRC |= _BV(UMSEL);
  //UCSRA = _BV(U2X);
}

void USART_TransmitByte( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

void USART_TransmitHex( unsigned char data )
{
	unsigned char h = data>>4;
	char ho = (h < 10) ? (h+'0') : (h+'A'-10);
	unsigned char l = data & 0xF;
	char lo = (l < 10) ? (l+'0') : (l+'A'-10);
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = ho;
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = lo;
}

void USART_TransmitText(char* data)
{
	while (*data != 0)
	{
		/* Wait for empty transmit buffer */
		while ( !( UCSRA & (1<<UDRE)) );
		/* Put data into buffer, sends the data */
		UDR = *data;
		data++;
	}
}

void USART_Transmit(void* p, unsigned long int len)
{
	unsigned char* buff = (unsigned char*)p;
	unsigned long int b;
	for (b = 0; b < len; b++) USART_TransmitByte(buff[b]);
}
