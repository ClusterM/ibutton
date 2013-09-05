#ifndef _USART_H
#define _USART_H

void USART_init(void);
void USART_TransmitByte( unsigned char data );
void USART_TransmitText(char* data);
void USART_Transmit(void* p, unsigned long int len);
void USART_TransmitHex(unsigned char data);

#endif
