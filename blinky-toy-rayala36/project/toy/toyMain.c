#include <msp430.h>
#include "libTimer.h"
#include "led-sound.h"
#include "buzzer.h"

int main() {

  //xWDTCTL = WDTPW | WDTHOLD;Disable Watchdog Timer

  //Establishes timing system for MSP430 board 
    configureClocks();
  // Buzzer is initialized;
    buzzer_init();
    enableWDTInterrupts();

  //Sets output bits in bottom board to the LED light bits
    P1DIR |= LEDS;
  //Both lights are initially off.
    P1OUT &= ~LEDS;

  //Resistors in bottom board are enabled
    P1REN |= SWITCHES;
  //Interrupts are enabled in bottom board  
    P1IE |= SWITCHES;
    P1OUT |= SWITCHES;
    P1IES |= SWITCHES;
    P1DIR &= ~SWITCHES;
    P1IFG &= ~SWITCHES;

    /* Enabling interrupt flags allows the microcontroller to respond to specific events or 
       conditions immediately by executing the corresponding ISR code. It helps the microcontroller
       handle time-sensitive tasks and respond to external events effectively, without constantly 
       checking for changes in the program flow. */

    P2IFG &= ~TOPSW;
    P2DIR &= ~TOPSW;
    P2REN |= TOPSW;
    P2IE  |= TOPSW;
    P2IES |= TOPSW;
    P2OUT |= TOPSW;

    or_sr(0x18);          // CPU off, GIE on
}

void toy_stateMachine();

/* Switch on P1 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if(P1IFG & SWITCHES){
    P1IFG &= ~SWITCHES;
    toy_stateMachine();
  }
}

/* Buttons on P2*/
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & TOPSW){
    P2IFG &= ~TOPSW;
    toy_stateMachine();
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT()
{
  toy_stateMachine();
}
