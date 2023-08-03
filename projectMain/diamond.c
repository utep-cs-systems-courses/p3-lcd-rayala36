#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "pongjuggle.h"

void drawDiamond(int cCol, int cRow, int size, u_int color)
{
    int c = 0;
    int r = 0;
    //Left half of the diamond is being drawn
    for(int j = 0; j < size; j++)
    {
      drawPixel(cCol+c, cRow+r, color);
      drawPixel(cCol+c, cRow-r, color);
      int upper = (cRow-r), lower = (cRow+r);
      for(;upper <= lower; upper++)
	drawPixel(cCol+c, upper, color);
      c += 1;
      r += 1;
    }

    //Right half of the diamond is being drawn
    for(int k = 0; k <= size; k++)
    {
      drawPixel(cCol+c, cRow+r, color);
      drawPixel(cCol+c, cRow-r, color);
      int upper = (cRow-r), lower = (cRow+r);
      for(;upper <= lower; upper++)
	drawPixel(cCol+c, upper, color);
      c += 1;
      r -= 1;
    }
}
