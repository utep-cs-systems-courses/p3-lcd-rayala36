#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int main() {
    configureClocks();
 
    buzzer_init();
    static int soundCount = 0;
    soundCount++;
    if (soundCount == 250){
       soundCount = 0;
       buzzer_set_period(1000);	/* start buzzing!!! 2MHz/1000 = 2kHz*/
    } 

    or_sr(0x18);          // CPU off, GIE on
}
