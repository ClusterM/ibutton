
======================================================

  ATMEL AVR UART Bootloader for AVR-GCC/avr-libc

  by Martin Thomas, Kaiserslautern, Germany
  mthomas@rhrk.uni-kl.de
  eversmith@heizung-thomas.de
  http://www.siwawi.arubi.uni-kl.de/avr_projects

  **  Addtional code and improvements contributed   **
  **  by Uwe Bonnes, Bjoern Riemer and Olaf Rempel. **
  
  Eearly versions of this bootloader-code have been
  based on the AVR Butterfly bootloader-source REV02
  which has been available from atmel.com.

======================================================


Programming-Software (on the "PC-Side"):

* AVRProg (included in AVRStudio) available at www.atmel.com.
  MS-Windows only. AVRProg can be used as stand-alone application.
  (avrprog.exe)

* avrdude available at http://savannah.nongnu.org/projects/avrdude/
  "Multiplattform"

* Installation instructions at the end of this file.


3. Dec. 2008 - Version 0.85

* disable U2X before jump to app as suggested be Alexander Döller
* moved UBRR-macros to main.c and changed them. Inspired by code from avr-libc setbaud.
  (macros which are commented out (//) are from Pavel Fertser)

6. Nov. 2008 - Version 0.84

* Added definitions for ATmega64 provided by Pavel Fertser - Thanks.

12. Apr. 2008 - Version 0.83

* Added definitions for ATmega644P and ATmega324P
* Tested with ATmega324P, gcc 4.2.2, avr-libc 1.4.6
* Added testapp to verify "exit bootloader" with
  watchdog (n.b.: watchdog-disable called early in testapp)

27. Jan. 2007 - Version 0.82

* Added definitions for ATmega644.
* Using avr-lib's eeprom-functions (old "direct-access"-code
  has not been compatible with ATmega644).
* Watchdog-disable at startup (configurable): avoids problems with
  repeated login to bootloader. Not needed if the bootloader is
  never re-entered again between an "exit programming" and
  a system-reset/power-toogle.
* Additional watchdog disable-function for ATmega644.
* Made watchdog-enable time at exit-programming a configuration-value 
  (define).
* Bootloader read-protection: if enabled the bootloader fakes
  an empty boot-section (configurable by define)
Since more of the avr-libc functions's are used this version
should be more portable for other AVRs but the size of the 
binary increases a little bit.
Make sure to disable the watchdog early in the user-application
esp. when using a "modern" AVR (i.e. ATmega48/88/168/644/324P/644P).

3. Dec. 2006 - Version 0.81

* Added definitions for ATmega162.
* Fixed init for double-speed (bitmask). Thanks to Bernhard Roth

28. May 2006 - Version 0.8beta3

* Supports discarding of interrupt-vectors which saves some space
  if no interrupts are needed in the bootloader. Added option 
  in makefile to enable this feature, modified LDFLAGS, 
  additional code in main.c for a pseudo default_interrupt ISR.
  The modified linker-scripts have been contributed by 
  Olaf Rempel (basicly just the .vector-section is not linked).
* Reverted the order of signatur-byte-numbers in part-
  configurations to the usual order in the datasheet, 
  also reverted in main.c for sending the signature.
* Definitions for lock/fuse-readout.
* Updated installation-instruction at the end of this file.
* Added DEVTYPE_ISP/DEVTYPE_BOOT to part-configurations,
  added configuration-option for this in main.c.
* A remark about the DEVTYPE: Usualy there are two
  Part-Codes/Device-Codes. One is for ISP: AVRProg shows 
  the type of the AVR. The other code is for bootloading:
  AVRprog shows the type plus "BOOT". When a boot-device-code 
  gets detected by AVRprog it "knows" how do handle the 
  limited functionality of bootloaders. (When receiving the
  ISP-code AVRProg expects an AVR910-type programmer.)
  The offset between the codes is usualy 0x01 where the 
  ISP-code is the smaller value, i.e. ATmega32 ISP-code 
  is 0x72->"ATmega32" and boot-code is 0x73->"ATmega32 BOOT".
  When using avrdude the bootloader's device-code must match
  the device-code in the avrdude.conf. Check the avrdude-
  code to see if both codes (AVR910 and AVR109) are supported.
  -- I have got some e-mails from users which have been 
  confused by this. Hopefully this explanation is good enough.
* This bootloader lets the watchdog do a reset when the
  user selects "Exit programmer" (i.e. in AVRProg) after an
  update. Make sure to disable or reset the watchdog early in 
  your application.

27. May 2006 - Version 0.8beta2

* More very well done improvements contributed by Olaf Rempel.
* Olaf Rempel also modified the STARTUP_WAIT method.

21. May 2006 - Version 0.8beta

* Version contributed by Olaf Rempel. He has done a lot of modifications.
  -> "cleaner code", smaller binaries.

09. Feb. 2006 - Version 0.75

* additional STARTUP_WAIT support contributed by Bjoern Riemer

18. Aug. 2005 - Version 0.74

* AT90CAN128 support contributed by Uwe Bonnes
* Makefile modifications contributed by Uwe Bonnes

23. Feb. 2005 - Version 0.7

* (Version 0.6 has never been available on the web-page)
* ATmega128 support
* code cleanup
* This version has been tested with ATmega8, ATmega32 and 
  ATmega128

7. Apr. 2004 - Version 0.5

* added different startup-methods
* compatible with ATmega8 now
* included makefile adapted to ATmega8 now
  (ATmega16 options still available)
* fixed jump to application which did not work
  reliably before
* tested with ATmega8
* minimal options and startup-code result in
  bootloader-size < 512 words

6. Apr. 2004 - Version 0.4

* Buffered read of chars from UART during programming
since eeprom-write is too slow for unbuffered
operation. So EEPROM-upload does work now.
* Added BOOTICE-mode to flash JTAGICE-compatible
hardware (ATmega16@7,3Mhz) (if you know about BOOTICE,
you may unterstand why this has been added, if not
just keep the option disabled)
* small changes in (my)boot.h (lock-bit-mask) found
out during the development of the STK-500-compatible
bootloader. But setting lock-bits still does not
work with this bootloader.
* read of the low-fuse byte works (high byte still TODO)
* read of the lock-byte works (write still TODO)

27. Mar 2004 - Version 0.3

Felt that as much functions from avr-libc's boot.h
as possible should be used without modifications.
Latest CVS-version of boot.h is included.
Only the read-routine is still "self-made" based
on ATMELs assembler-code.
EEPROM write on Mega16 does not work (and did not
work with V0.2 too). May be caused by my old Mega16
chip. Needs testing. Flash read/write and EEPROM
read works. Still only tested with ATmega16.
This version may not work with the ATmega169 any
more.

24. Mar 2004 - Version 0.2

During the development of a data-logger application
with the AVR-Butterfly there was a need to make
some changes in the bootloader. The same problem
again: no IAR compiler. The same way to solve the
problem: a port of the code to avr-gcc/avr-libc.
So this code is based on the ATMEL Butterfly
bootloader source code Rev 0.2 for IAR.

The bootloader-port for the Butterfly which mimics
the complete functionality of the original
BF-bootloader is availabe at:
www.siwawi.arubi.uni-kl.de/avr_projects

Atmel used a separate "lib" written in "pure"
assembly to access the low-level functions
for flash read/write. Well, so far I
don't know how to use "mixed language sources"
with the avr-gcc toolchain, so the low-level
routines have been implemented as inline assembler.
The avr-libc boot.h module written by Eric
Weddington served as a template  Three of the four
low-level routines found in lowlevel.c come from
boot.h with minimal changes. The read routine has
been developed based on the ATMEL assembler code.

Ignore the fuse and lock-bit readout. Read and Set is
not enabled (TODO).


--------------- Installation -----------------

- Change the MCU type in the makefile.

- Change the boot(loader)-size in Makefile. The needed
  space depends on the features selected in main.c

- Set baudrate in main.c, a doublespeed configuration-option
  is available too.

- Change the F_CPU in main.c to the clock-frequency
  of your board. See the datasheet for frequencies 
  with minimum error at the selected baudrate.

- Select the start-condition in main.c. 

- Please use at least avr-gcc 3.3.1/avr-libc 1.0
  or WINAVR Sept. 2003 or later to compile and link
  this bootloader.

- Upload the hex-File to the AVR (STK500, STK200, SP12
  evertool, AVR910 etc.)

- Program the "Boot Flash section size" (BOOTSZ fuses)
  according to the boot-size selected in the makefile
  i.e. BOOTSZ=00 for boot-size 1024 words (2048 bytes)
  on ATmega16

- enable the BOOT Reset Vector fuse (BOOTRST=0)

- Set the lock bits to protect the bootloader from
  SPM-writes (Boot Loader Protection Mode 2 in STK500-
  plugin) so that it can not overwrite itself.

- Connect the AVR UART Pins via level-shifter/inverter
  (i.e. MAX232) to your PCs COM-Port.

- Reset the AVR while fullfilling the bootloader start-
  condition. (Default: selected pin connected to GND). 
  The condition must be "true" until you see the 
  AVRPROG dialog or avrdude connects.

- Start AVRPROG (AVRStudio/Tools or stand-alone avrprog.exe)
  AVRDUDE is supported too, check it's manual 
  for command-line options. Read the text above for
  information about Device-Types and AVRDUDE

- AVRPROG or AVRDUDE should detect the bootloader.

- see AVRStudio's online-help for more information how
  to use AVRPROG

- make sure to EXIT from AVRPROG (button) to start
  your main-application or toogle power/reset.


Feedback welcome, Good luck.
Martin
