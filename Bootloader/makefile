# Hey Emacs, this is a -*- makefile -*-
#
# Makefile for the AVRProg-compatible Bootloader
#
# based on the 
# WinAVR Sample makefile written by Eric B. Weddington, Jörg Wunsch, et al.
# Released to the Public Domain
# Please read the make user manual!
#
# Additional material for this makefile was submitted by:
#  Tim Henigan
#  Peter Fleury
#  Reiner Patommel
#  Sander Pool
#  Frederik Rouleau
#  Markus Pfaff
#
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF (for use with AVR Studio 3.x or VMLAB).
#
# make extcoff = Convert ELF to AVR Extended COFF (for use with AVR Studio
#                4.07 or greater).
#
# make program = Download the hex file to the device, using avrdude.  Please
#                customize the avrdude settings below first!
#
# make filename.s = Just compile filename.c into the assembler code only
#
# To rebuild project do "make clean" then "make all".
#

# user defined values

# MCU name
## MCU = atmega8
#F_CPU = 11059200UL
#F_CPU = 8000000UL
#BAUDRATE = 9600
MCU = atmega8
LFUSE          = E4
HFUSE          = DA
MCU_PROGRAMMER = m8
## MCU = atmega162
## MCU = atmega169
## MCU = atmega32
## MCU = atmega324p
## MCU = atmega64
## MCU = atmega644
## MCU = atmega644p
## MCU = atmega128
## MCU = at90can128

################## BOOTLOADER ######################
#  mt: Boot loader support. So far not done with a separate section
#  to get the interrupt vector into the bootloader area (for BOOTINTVEC=yes).
#  Bootloader address in datasheet and stk500 is given as
#  "word", gcc toolchain needs "byte"-address
#  (see LDFLAGS further down)

#/* Select Boot Size in Words (select one, comment out the others) */
## NO! BOOTSIZE=128
## NO! BOOTSIZE=256
BOOTSIZE=512
#BOOTSIZE=1024
## BOOTSIZE=2048

# /* Select if bootloader should include the inverrupt-vectors 
# when selecting 'no' here, the bootloader must not use
# any interrupts and the modified linker-scripts are used. */
##BOOTINTVEC=yes
BOOTINTVEC=no

##
ifeq ($(MCU), atmega8)
BFD_MACH=avr4
ifeq ($(BOOTSIZE), 128)
	MT_BOOTLOADER_ADDRESS = 0x1F00
endif
ifeq ($(BOOTSIZE), 256)
	MT_BOOTLOADER_ADDRESS = 0x1E00
endif
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x1C00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x1800
endif
endif

##
ifeq ($(MCU), atmega16)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 128)
	MT_BOOTLOADER_ADDRESS = 0x3F00
endif
ifeq ($(BOOTSIZE), 256)
	MT_BOOTLOADER_ADDRESS = 0x3E00
endif
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x3C00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x3800
endif
endif

##
ifeq ($(MCU), atmega162)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 128)
	MT_BOOTLOADER_ADDRESS = 0x3F00
endif
ifeq ($(BOOTSIZE), 256)
	MT_BOOTLOADER_ADDRESS = 0x3E00
endif
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x3C00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x3800
endif
endif

##
ifeq ($(MCU), atmega169)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 128)
	MT_BOOTLOADER_ADDRESS = 0x3F00
endif
ifeq ($(BOOTSIZE), 256)
	MT_BOOTLOADER_ADDRESS = 0x3E00
endif
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x3C00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x3800
endif
endif

##
ifeq ($(MCU), atmega32)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 256)
	MT_BOOTLOADER_ADDRESS = 0x7E00
endif
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x7C00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x7800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0x7000
endif
endif

##
ifeq ($(MCU), atmega324p)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 256)
	MT_BOOTLOADER_ADDRESS = 0x7E00
endif
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x7C00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x7800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0x7000
endif
endif

##
ifeq ($(MCU), atmega64)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0xFC00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0xF800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0xF000
endif
ifeq ($(BOOTSIZE), 4096)
	MT_BOOTLOADER_ADDRESS = 0xE000
endif
endif

##
ifeq ($(MCU), atmega644)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0xFC00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0xF800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0xF000
endif
ifeq ($(BOOTSIZE), 4096)
	MT_BOOTLOADER_ADDRESS = 0xE000
endif
endif

##
ifeq ($(MCU), atmega644p)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0xFC00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0xF800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0xF000
endif
ifeq ($(BOOTSIZE), 4096)
	MT_BOOTLOADER_ADDRESS = 0xE000
endif
endif

##
ifeq ($(MCU), atmega128)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x1FC00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x1F800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0x1F000
endif
ifeq ($(BOOTSIZE), 4096)
	MT_BOOTLOADER_ADDRESS = 0x1E000
endif
endif

##
ifeq ($(MCU), at90can128)
BFD_MACH=avr5
ifeq ($(BOOTSIZE), 512)
	MT_BOOTLOADER_ADDRESS = 0x1FC00
endif
ifeq ($(BOOTSIZE), 1024)
	MT_BOOTLOADER_ADDRESS = 0x1F800
endif
ifeq ($(BOOTSIZE), 2048)
	MT_BOOTLOADER_ADDRESS = 0x1F000
endif
ifeq ($(BOOTSIZE), 4096)
	MT_BOOTLOADER_ADDRESS = 0x1E000
endif
endif


# Output format. (can be srec, ihex, binary)
FORMAT = ihex
#FORMAT = srec

# Target file name (without extension).
TARGET = main


# List C source files here. (C dependencies are automatically generated.)
SRC = $(TARGET).c


# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC =



# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS =


# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options here
CDEFS = -DBOOTSIZE=$(BOOTSIZE)

# Place -I options here
CINCS =


# Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS) $(CINCS)
CFLAGS += -O$(OPT)
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -Wall -Wstrict-prototypes
CFLAGS += -Wa,-adhlns=$(<:.c=.lst)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS += $(CSTANDARD)



# Assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs



#Additional libraries.

# Minimalistic printf version
PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt

PRINTF_LIB =

# Minimalistic scanf version
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt

SCANF_LIB =

MATH_LIB = -lm

# External memory options

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)

################## BOOTLOADER ######################
# MT_BOOTLOADER_ADDRESS (=Start of Boot Loader section
# in bytes - not words) as defined above.
LDFLAGS += -Wl,--section-start=.text=$(MT_BOOTLOADER_ADDRESS)

# check if linker-scripts without interrupt-vectors should
# be used and set linker-option, announce to C-code by define
ifeq ($(BOOTINTVEC), no)
LDFLAGS += -T./ldscripts_no_vector/$(BFD_MACH).x
CFLAGS  += -DBOOTLOADERHASNOVECTORS
endif


# Programming support using avrdude. Settings and variables.

# Programming hardware: alf avr910 avrisp bascom bsd
# dt006 pavr picoweb pony-stk200 sp12 stk200 stk500
#
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE_PROGRAMMER = stk500v2

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = com1    # programmer connected to serial device
#AVRDUDE_PORT = /dev/ttyS0    # programmer connected to serial device

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep


# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_VERBOSE = -v -v

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)



# ---------------------------------------------------------------------------

# Define directories, if needed.
#DIRAVR = c:/winavr
#DIRAVRBIN = $(DIRAVR)/bin
#DIRAVRUTILS = $(DIRAVR)/utils/bin
#DIRINC = .
#DIRLIB = $(DIRAVR)/avr/lib


# Define programs and commands.
#SHELL = $(DIRAVRUTILS)/sh
#NM = $(DIRAVRBIN)/avr-nm
#CC = $(DIRAVRBIN)/avr-gcc
#OBJCOPY = $(DIRAVRBIN)/avr-objcopy
#OBJDUMP= $(DIRAVRBIN)/avr-objdump
#SIZE = $(DIRAVRBIN)/avr-size
#AVRDUDE = $(DIRAVRBIN)/avrdude.sh
#REMOVE = rm -f
#COPY = cp

# Define programs and commands.
SHELL = sh
CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
COPY = cp
WINSHELL = cmd


# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:




# Define all object files.
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)


# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)





# Default target.
all: begin gccversion sizebefore build sizeafter finished end

build: elf hex eep lss sym

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss
sym: $(TARGET).sym



# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -x -A $(TARGET).elf
sizebefore:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi



# Display compiler version information.
gccversion :
	@$(CC) --version



# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000


coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof


extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@



# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)


# Compile: create object files from C source files.
%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@



# Target: clean project.
clean: begin clean_list finished end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) .dep/*



# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex eep lss sym coff extcoff \
clean clean_list program

program: hex
	avrdude -p $(MCU_PROGRAMMER) -c avrisp2 -P usb -U flash:w:main.hex -U lfuse:w:0x$(LFUSE):m -U hfuse:w:0x$(HFUSE):m -v -e
#	avrdude -V -p $(MCU_PROGRAMMER) -c ftbb -P ft0 -U flash:w:main.hex -U lfuse:w:0x$(LFUSE):m -U hfuse:w:0x$(HFUSE):m -D
