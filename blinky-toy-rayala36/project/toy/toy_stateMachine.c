#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led-sound.h"

void
toy_stateMachine()
{
  char p1val = P1IN;            /* Detects input in the bottom board */
  char p2val = P2IN;		/* Detects input in the top board */

  int press = 0;
  
  if( (P2IN & TOPS1)? 0 : 1 )
  {
    /* down=(Dim-to-bright) green LED and (Low-to-High) buzz */
      greenTimeAdvStateMachines();
      P1OUT &= ~LED_RED;

    /* Detects if TOPS2 (or S2 on the top board) is pressed.  If so, a pattern involving the red 
       light and buzzer will occur and the green light will remain off as long as the button is 
       pressed down.  Otherwise, the toy will remain in a default state. */
  } else if( (P2IN & TOPS2) ? 0 : 1 )
  {
    /* down=(Bright-to-dim) red LED and (High-to-Low) buzz*/
    redTimeAdvStateMachines();
    P1OUT &= ~LED_GREEN;

    /* Detects if TOPS3 (or S3 on the top board) is pressed.  If so, a pattern involving both 
       lights and the buzzer will occur as long as the button is pressed down.  Otherwise, the toy
       will remain in a default state. */
  } else if( (P2IN & TOPS3)? 0 : 1 )
  {
    // A little song that corresponds with the lights.
    siren();
    /* Detects if TOPS4 (or S4 on the top board) is pressed.  If so, a pattern involving the buzzer
       will occur as long as the button is pressed down. Otherwise, the toy will remain in a 
       default state */
  } else if ( (P2IN & TOPS4)? 0 : 1 )
  {
    song2();
    P1OUT &= ~LEDS;
  } else if ( (P1IN & SW1)? 0 : 1)
  {
    /* did a button cause this interrupt? */
    /* A siren involving sound and lights, not unlike a police car siren.*/
    buzzer_set_period(0);
    P1OUT &= ~LEDS;
  }
}
