//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

// If the int value is nonzero, the green light is on; it is off, otherwise.
void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}

/* The blinkCount value incrememnts, and whenever it reaches the blinkLimit value, the light is 
   turned on and the blinkCount value resets.  The light spends of the rest of the time off.
*/

// blink state machine
static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle 
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    greenControl(1);
  } else
    greenControl(0);
}

/* The blinkLimit value will increment/decrementt 7 times before being reset; the light will be set
   to go from bright to dim or dim to bright, respectively.
*/

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit --;  // increase duty cycle
  if (blinkLimit <= 0)  // but don't let duty cycle go above 1/7.
    blinkLimit = 8;
}

// Enables all previous functions to occur by updating them every second.
void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  }
}

/* The green light will be turned on with "blinkUpdate" with its pattern and the blink limit value
   is updated with "secondUpdate."
*/
void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking   
  timeAdvStateMachines();
} 

