#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "pongjuggle.h"

short drawPos3[2];
short controlPos3[2];
short colVelocity3;
short colLimits3[2];

void
draw_offense(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 28, 3, color);
}

void
screen_update_offense()
{
  for (char axis3 = 0; axis3 < 2; axis3 ++) 
    if (drawPos3[axis3] != controlPos3[axis3]) /* position changed? */
      goto redraw3;
  return;			/* nothing to do */
 redraw3:
  draw_offense(drawPos3[0], drawPos3[1], COLOR_BLACK); /* erase */
  for (char axis3 = 0; axis3 < 2; axis3 ++)
    drawPos3[axis3] = controlPos3[axis3];
  draw_offense(drawPos3[0], drawPos3[1], COLOR_WHITE); /* draw */
}  
