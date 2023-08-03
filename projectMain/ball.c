#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "pongjuggle.h"

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 6, 6, color);
}
