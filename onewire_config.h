#ifndef __onewire_config_h_included__
#define __onewire_config_h_included__

#include "bits.h"

#define ONEWIRE_PORT PORTD
#define ONEWIRE_DDR DDRD
#define ONEWIRE_PIN PIND
#define ONEWIRE_MASTER_TX_PIN 5
#define ONEWIRE_MASTER_RX_PIN 6

#define ONEWIRE_TIMER_INIT { set_bit(TCCR1B, CS11); unset_bit2(TCCR1B, CS12, CS10); } // 8x timer
#define ONEWIRE_TIMER_REG TCNT1
#define ONEWIRE_USEC (F_CPU / 8000000UL)

#endif
