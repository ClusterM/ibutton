#ifndef _MEGA644P_H_
#define _MEGA644P_H_

/* I (M. Thomas) could not find an official Boot-ID 
   for the ATmega644P so pretend it's an ATmega64 */
/* Part-Code ISP */
#define DEVTYPE_ISP     0x45
/* Part-Code Boot */
#define DEVTYPE_BOOT    0x46

#define SIG_BYTE1	0x1E
#define SIG_BYTE2	0x96
#define SIG_BYTE3	0x0A

#include "megaxx4p.h"

#endif // #ifndef _MEGA644P_H_
