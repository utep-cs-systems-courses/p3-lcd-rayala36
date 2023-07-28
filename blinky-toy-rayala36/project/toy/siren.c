#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led-sound.h"

//Entire siren will last for 1/5 of a second.
void siren(){

  /* For the first 1/10 of a second, only the green LED will be lit and the buzzer will sound at 
     2kHz.*/
  static int secondCount = 0;
  secondCount ++;
    if (secondCount <= 25) { 	/* once each sec... */
       P1OUT |= LED_GREEN;
       P1OUT &= ~LED_RED;
       buzzer_set_period(1000);
       // Once 1/5 of a second has been reached, the siren will reset.
    } else if (secondCount > 25 && secondCount < 50) {
      /* For the second 1/10 of a second, only the red LED will be lit and the buzzer will sound 
	 at about 1 and 1/3 kHz.*/
       P1OUT |= LED_RED;
       P1OUT &= ~LED_GREEN;
       buzzer_set_period(1500);
    }
    else if (secondCount == 50)
      secondCount = 0;
}
