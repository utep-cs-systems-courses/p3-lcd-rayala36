#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led-sound.h"

void song(){

  /* Using the buzzTime variable, which continuously increases until it reaches 900 and resets, 
     the buzzer will be set to certain frequencies.  Additionally, the red and green LED's will 
     toggle with each change in pitch in the buzzer.*/
  
  static int buzzTime = 0;
  buzzTime ++;
    if (buzzTime == 25){
      buzzer_set_period(1000);
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    } else if (buzzTime == 50){
      buzzer_set_period(1100);
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
      
    } else if (buzzTime == 75){
      buzzer_set_period(800);
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
      
    } else if (buzzTime == 200){
      buzzer_set_period(1000);
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    } else if (buzzTime == 260){
      buzzer_set_period(800);
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    } else if (buzzTime == 320){
      buzzer_set_period(700);
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    } else if (buzzTime == 380){
      buzzer_set_period(600);
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
      
    } else if (buzzTime == 440){
      buzzer_set_period(600);
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    } else if (buzzTime == 465){
      buzzer_set_period(800);
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    } else if (buzzTime == 515){
      buzzer_set_period(600);
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    } else if (buzzTime == 540)
      buzzTime = 0;
}
