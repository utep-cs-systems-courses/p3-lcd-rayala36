#ifndef led_included
#define led_included

#define LED_RED BIT6
#define LED_GREEN BIT0
#define LEDS (BIT0 | BIT6)

#define SW1 BIT3
#define SWITCHES SW1

#define TOPS1 BIT0
#define TOPS2 BIT1
#define TOPS3 BIT2
#define TOPS4 BIT3
#define TOPSW (TOPS1 | TOPS2 | TOPS3 | TOPS4)

void greenTimeAdvStateMachines();
void redTimeAdvStateMachines();
void toy_stateMachine();
void siren();
void song();
void song2();

#endif // included
