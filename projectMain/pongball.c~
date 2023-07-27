#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "pong.h"

short drawPos[2] = {1, 10}, controlPos[2] = {2, 10};
short colVelocity = 5, rowVelocity = 5;
short rowLimits[2] = {1, screenHeight}, colLimits[2] = {1, screenWidth - 23};

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 6, 6, color);
}

void
screen_update_ball()
{
  for (char axis = 0; axis < 2; axis ++) 
    if (drawPos[axis] != controlPos[axis]) /* position changed? */
      goto redraw;
  return;			/* nothing to do */
 redraw:
  draw_ball(drawPos[0], drawPos[1], COLOR_BLACK); /* erase */
  for (char axis = 0; axis < 2; axis ++)
    drawPos[axis] = controlPos[axis];
  draw_ball(drawPos[0], drawPos[1], COLOR_WHITE); /* draw */
}
