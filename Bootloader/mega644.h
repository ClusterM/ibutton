#ifndef _MEGA644_H_
#define _MEGA644_H_

/* I (M. Thomas) could not find an official Boot-ID 
   for the ATmega644 so pretend it's an ATmega64 */
/* Part-Code ISP */
#define DEVTYPE_ISP     0x45
/* Part-Code Boot */
#define DEVTYPE_BOOT    0x46

#define SIG_BYTE1	0x1E
#define SIG_BYTE2	0x96
#define SIG_BYTE3	0x09

#define UART_BAUD_HIGH	UBRR0H
#define UART_BAUD_LOW	UBRR0L
#define UART_STATUS	    UCSR0A
#define UART_TXREADY	UDRE0
#define UART_RXREADY	RXC0
#define UART_DOUBLE	    U2X0
#define UART_CTRL	    UCSR0B
#define UART_CTRL_DATA	((1<<TXEN0) | (1<<RXEN0))
#define UART_CTRL2	    UCSR0C
#define UART_CTRL2_DATA	( (1<<UCSZ01) | (1<<UCSZ00))
#define UART_DATA	    UDR0

#define WDT_OFF_SPECIAL
static inline void bootloader_wdt_off(void)
{
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;
}


#endif // #ifndef _MEGA644_H_
