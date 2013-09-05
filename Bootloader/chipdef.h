#ifndef CHIPDEF_H
#define CHIPDEF_H

#include <avr/io.h>

#if defined (SPMCSR)
#define SPM_REG SPMCSR
#elif defined (SPMCR)
#define SPM_REG SPMCR
#else
#error "AVR processor does not provide bootloader support!"
#endif

#define APP_END (FLASHEND - (BOOTSIZE * 2))

#if (SPM_PAGESIZE > UINT8_MAX)
typedef uint16_t pagebuf_t;
#else
typedef uint8_t pagebuf_t;
#endif

#if defined(__AVR_ATmega169__)
#include "mega169.h"

#elif defined(__AVR_ATmega16__)
#include "mega16.h"

#elif defined(__AVR_ATmega162__)
#include "mega162.h"

#elif defined(__AVR_ATmega8__)
#include "mega8.h"

#elif defined(__AVR_ATmega32__)
#include "mega32.h"

#elif defined(__AVR_ATmega324P__)
#include "mega324p.h"

#elif defined(__AVR_ATmega64__)
#include "mega64.h"

#elif defined(__AVR_ATmega644__)
#include "mega644.h"

#elif defined(__AVR_ATmega644P__)
#include "mega644p.h"

#elif defined(__AVR_ATmega128__)
#include "mega128.h"

#elif defined(__AVR_AT90CAN128__)
#include "mega128can.h"

#else
#error "no definition for MCU available in chipdef.h"
#endif

#endif
