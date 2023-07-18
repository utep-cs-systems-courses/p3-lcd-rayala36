#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led-sound.h"

void redControl(int On)
{
  if (On) {
    P1OUT |= LED_RED;
  } else {
    P1OUT &= ~LED_RED;
  }
}

// State Machine for Red Light (Bright to Low) and Buzzer (High to Low)
static int blinkLimit2 = 5;   //  state var representing reciprocal of duty cycle

void blinkUpdateR()
{
  // As long as the blink count does not pass the blink limit, the light will remain on.
  static int blinkCount2 = 0; // state var representing blink state
  blinkCount2 ++;
  // The buzzer's frequency corresponds with the blink count.
  buzzer_set_period( (1000 + (blinkCount2*100)) );
  if (blinkCount2 >= blinkLimit2) {
    blinkCount2 = 0;
    redControl(1);
  }
  else
    redControl(0);
}

/* Enables the light to go from brigh to dim by decreasing duty cycle; the lower the duty cycle, 
   the dimmer the light. */
void oncePerSecondR() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit2 ++;  // Reduce duty cycle
  if (blinkLimit2 >= 8)  // but don't let duty cycle go below 1/7.
    blinkLimit2 = 0;
}

// Speed at which red light will dim and buzzer will decrease in frequency.
// In this case, each state of the buzzer and red light will remain on for 12% of a second.
void secondUpdateR()
{
  static int secondCount2 = 0;
  secondCount2 ++;
  if (secondCount2 >= 30){
    secondCount2 = 0;
    oncePerSecondR();
  }
}

void redTimeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdateR();
  secondUpdateR();
}
