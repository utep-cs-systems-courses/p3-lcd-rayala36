#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "pongjuggle.h"

void
update_shape(int on)
{
  screen_update_ball();
  screen_update_defense();
  screen_update_offense();
  return on;
}
