#include <msp430.h>
#include <libTimer.h>
#include <stdlib.h>
#include <string.h>
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "pongjuggle.h"

void scoreJT(int score)
{
  switch (score)
      {
	case 1:
	  buzzer_set_period(900);
	  break;
	case 2:
	  buzzer_set_period(700);
	  break;
	case 3:
	  buzzer_set_period(650);
	  break;
	case 4:
	  buzzer_set_period(600);
	  break;
        default:
	  break;
      }
}
