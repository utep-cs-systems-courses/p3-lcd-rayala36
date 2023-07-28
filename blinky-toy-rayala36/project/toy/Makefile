# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: toy-c.elf toy-s.elf 

#additional rules for files
toy-c.elf: ${COMMON_OBJECTS} toy_stateMachine.o siren.o song.o song2.o buzzer.o toyMain.o greenStateMach.o redStateMach.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

toy-s.elf: ${COMMON_OBJECTS} toy_stateMachine.o siren-s.o song.o song2.o buzzer.o toyMain.o greenStateMach.o redStateMach.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load-c: toy-c.elf
	msp430loader.sh  $^

load-s: toy-s.elf
	msp430loader.sh $^

clean: $^
	rm -f *.o *.elf


