#ifndef _MEGA324P_H_
#define _MEGA324P_H_

/* I (M. Thomas) could not find an official Boot-ID 
   for the ATmega324P so pretend it's an ATmega32 */
/* Part-Code ISP */
#define DEVTYPE_ISP     0x72
/* Part-Code Boot */
#define DEVTYPE_BOOT    0x73

#define SIG_BYTE1	0x1E
#define SIG_BYTE2	0x95
#define SIG_BYTE3	0x08

#include "megaxx4p.h"

#endif // #ifndef _MEGA324P_H_
