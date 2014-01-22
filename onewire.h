#ifndef __onewire_h_included__
#define __onewire_h_included__

#include "onewire_config.h"

#define ONEWIRE_WAIT(t) {ONEWIRE_TIMER_REG=0; while(ONEWIRE_TIMER_REG < ONEWIRE_USEC * t);}

#define ONEWIRE_COMMAND_READ_ROM 0x33
#define ONEWIRE_COMMAND_READ_ROM_ALT 0x0F
#define ONEWIRE_COMMAND_MATCH_ROM 0x55
#define ONEWIRE_COMMAND_READ_SCRATCHPAD 0xBE
#define ONEWIRE_COMMAND_WRITE_SCRATCHPAD 0x4E
#define ONEWIRE_COMMAND_COPY_SCRATCHPAD 0x4E
#define ONEWIRE_COMMAND_SKIP_ROM 0xCC
#define ONEWIRE_COMMAND_CONVERT 0x44
#define ONEWIRE_COMMAND_SEARCH 0xF0

#define ONEWIRE_MASTER_TX_ON ONEWIRE_DDR |= 1<<ONEWIRE_MASTER_TX_PIN
#define ONEWIRE_MASTER_TX_OFF ONEWIRE_DDR &= ~(1<<ONEWIRE_MASTER_TX_PIN)
#define ONEWIRE_MASTER_TX(t) {ONEWIRE_MASTER_TX_ON; ONEWIRE_WAIT(t); ONEWIRE_MASTER_TX_OFF;}
#define ONEWIRE_MASTER_RX (((ONEWIRE_PIN>>ONEWIRE_MASTER_RX_PIN) & 1) == 0)
#define ONEWIRE_WRITE1 { ONEWIRE_MASTER_TX(10); ONEWIRE_WAIT(75); }
#define ONEWIRE_WRITE0 { ONEWIRE_MASTER_TX(75); ONEWIRE_WAIT(10); }

void onewire_init();
char onewire_write_reset();
char onewire_read_bit();
unsigned char onewire_read_byte();
void onewire_write_bit(unsigned char b);
void onewire_write_byte(unsigned char b);
void onewire_pullup();
void onewire_search_all(void (*f)(unsigned char* out));
char onewire_check_crc(unsigned char* data, unsigned char size);
char onewire_all_zeros(unsigned char* data, unsigned char size);

#endif