# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:pongjuggle.elf

#additional rules for files
pongjuggle.elf: ${COMMON_OBJECTS} update_shape.o draw_offense.o draw_defense.c draw_ball.o diamond.o  project.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: pongjuggle.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
