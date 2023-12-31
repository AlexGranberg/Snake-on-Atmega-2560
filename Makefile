CC=C:\avr\bin\avr-gcc
LD=C:\avr\bin\avr-ld
OBJCOPY="C:\avr\bin\avr-objcopy"
OBJDUMP="C:\avr\bin\avr-objdump"
AVRSIZE="C:\avr\bin\avr-size"
OBJISP="C:\avr\bin\avrdude"
MCU=atmega2560
CFLAGS=-Wall -Wextra -Wundef -pedantic \
		-Os -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU} -DBAUD=11500
LDFLAGS=-mmcu=$(MCU)
PORT=\\\\.\\COM3
BIN=Snake
OUT=${BIN}.hex
SOURCES = main.c millis.c uart.c max72xx.c analogRead.c gameText.c snake.c generalFunctions.c

DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

OBJS = $(addprefix $(OUTPUTDIR)/,$(SOURCES:.c=.o))

all: $(OUTPUTDIR)  $(OUT) 

$(OBJS): Makefile

$(OUTPUTDIR)/%.o:%.c
	$(CC) $(CFLAGS) -MD -o $@ -c $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@


$(OBJS):$(SOURCES)

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}.hex
	$(OBJISP)  -v -V -patmega2560 -cwiring "-PCOM13" -b115200 -D "-Uflash:w:$<


clean:
	del "$(OUT)"  *.map *.P *.d

$(OUTPUTDIR): 
	@mkdir "$(OUTPUTDIR)"
		   	
.PHONY: clean dirs