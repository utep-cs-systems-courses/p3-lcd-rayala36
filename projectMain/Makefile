# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all:pongjuggle.elf

#additional rules for files
pongjuggle-c.elf: ${COMMON_OBJECTS} scoreJT.o buzzer.o update_shape.o draw_offense.o draw_defense.c draw_ball.o diamond.o  project.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

pongjuggle-s.elf: ${COMMON_OBJECTS} scoreJT-s.s buzzer.o update_shape-s.o draw_offense.o draw_defense.c draw_ball.o diamond-s.o project.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-c: pongjuggle-c.elf
	msp430loader.sh $^

load-s: pongjuggle-s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
