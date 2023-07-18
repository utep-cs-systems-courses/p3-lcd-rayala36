#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led-sound.h"

void song2(){  

  /* Using the buzzTime2 variable, which continuously increases until it reaches 1020 and resets, 
     the buzzer will be set to certain frequencies for a period of 1/10 of a second.  */
  
  static int buzzTime2 = 0;
  buzzTime2++;
  if (buzzTime2 == 125)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(592);
  if (buzzTime2 == 185)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(0);
  if (buzzTime2 == 210)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(592);
  if (buzzTime2 == 270)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(705);
  if (buzzTime2 == 300)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(790);

  
  if (buzzTime2 == 360)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(592);
  if (buzzTime2 == 420)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(0);
  if (buzzTime2 == 450)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(592);
  
  if (buzzTime2 == 510)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(530);
  if (buzzTime2 == 540)
    for(int x = 0; x < 25; x++)
      buzzer_set_period(560);
  
  if (buzzTime2 == 550)
    buzzTime2 = 0;
  
}  

