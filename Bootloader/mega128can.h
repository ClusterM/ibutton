#ifndef _MEGA128CAN_H_
#define _MEGA128CAN_H_

/* Dummy: use ATmega128 device-code for now, 
   must be same as used in avrdude.conf */
/* Part-Code ISP */
#define DEVTYPE_ISP     0x43
/* Part-Code Boot */
#define DEVTYPE_BOOT    0x44

#define SIG_BYTE1	0x1E
#define SIG_BYTE2	0x97
#define SIG_BYTE3	0x81


#ifndef UART_USE_SECOND
#define UART_BAUD_HIGH	UBRR0H
#define UART_BAUD_LOW	UBRR0L
#define UART_STATUS	UCSR0A
#define UART_TXREADY	UDRE0
#define UART_RXREADY	RXC0
#define UART_DOUBLE	U2X0
#define UART_CTRL	UCSR0B
#define UART_CTRL_DATA	((1<<TXEN0) | (1<<RXEN0))
#define UART_CTRL2	UCSR0C
#define UART_CTRL2_DATA	((1<<UCSZ01) | (1<<UCSZ00))
#define UART_DATA	UDR0
#else
#define UART_BAUD_HIGH	UBRR1H
#define UART_BAUD_LOW	UBRR1L
#define UART_STATUS	UCSR1A
#define UART_TXREADY	UDRE1
#define UART_RXREADY	RXC1
#define UART_DOUBLE	U2X1
#define UART_CTRL	UCSR1B
#define UART_CTRL_DATA	((1<<TXEN1) | (1<<RXEN1))
#define UART_CTRL2	UCSR1C
#define UART_CTRL2_DATA	((1<<UCSZ11) | (1<<UCSZ10))
#define UART_DATA	UDR1
#endif

#endif // #ifndef _MEGA128CAN_H_
