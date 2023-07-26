#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

char blue = 31, green = 0, red = 31;
unsigned char step = 0;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 6, 6, color);
}

// axis zero for col, axis 1 for row
short drawPos[2] = {1, screenHeight >> 1}, controlPos[2] = {2, 10};
short colVelocity = 5, rowVelocity = 5;
short rowLimits[2] = {0, screenHeight}, colLimits[2] = {1, screenWidth - 3};

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

// axis zero for col, axis 1 for row
short drawPos2[2] = {1, 5}, controlPos2[2] = {2, 5};
short colVelocity2 = 8, colLimits2[2] = {1, screenWidth - 20};

void
draw_defense(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 28, 3, color);
}

void
screen_update_defense()
{
  for (char axis2 = 0; axis2 < 2; axis2 ++) 
    if (drawPos2[axis2] != controlPos2[axis2]) /* position changed? */
      goto redraw2;
  return;			/* nothing to do */
 redraw2:
  draw_defense(drawPos2[0], drawPos2[1], COLOR_BLACK); /* erase */
  for (char axis2 = 0; axis2 < 2; axis2 ++)
    drawPos2[axis2] = controlPos2[axis2];
  draw_defense(drawPos2[0], drawPos2[1], COLOR_WHITE); /* draw */
}  

// axis zero for col, axis 1 for row
short drawPos3[2] = {1, screenHeight-6}, controlPos3[2] = {2, screenHeight-6};
short colVelocity3 = 5, colLimits3[2] = {1, screenWidth - 20};

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

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
   
    {				/* move ball */
      short oldCol = controlPos[0];
      short newCol = oldCol + colVelocity;
      short oldRow = controlPos[1];
      short newRow = oldRow + rowVelocity;

      if (newCol <= colLimits[0] || newCol >= colLimits[1])
	colVelocity = -colVelocity;
      else
	controlPos[0] = newCol;

      if( newRow <= rowLimits[0] || newRow >= rowLimits[1])
	rowVelocity = -rowVelocity;
      else
	controlPos[1] = newRow;

                                /* move defense board*/
      short oldCol2 = controlPos2[0];
      short newCol2 = oldCol2 + colVelocity2;
      if(newCol2 <= colLimits2[0] || newCol2 >= colLimits2[1])
        colVelocity2 = -colVelocity2;
      else
	controlPos2[0] = newCol2;
    }

    {				/* update player (offense) board */
      short oldCol3 = controlPos3[0];
      short newCol3 = oldCol3 + colVelocity3;
      if (switches & SW3){
         if(newCol3 <= colLimits3[0] || newCol3 >= colLimits3[1])
            colVelocity3 = -colVelocity3;
         else
	    controlPos3[0] = newCol3;
      }
      if (switches & SW2){
	colVelocity3 = -(colVelocity3 * 2);
      }

      if (switches & SW1)
         colVelocity3 = 5;
      if (step <= 30)
	step ++;
      else
	step = 0;
      secCount = 0;
    }
    if (switches & SW4) return;
    redrawScreen = 1;
  }
}
  
void update_shape();

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}
/*
void
screen_update_hourglass()
{
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char lastStep = 0;
  
  if (step == 0 || (lastStep > step)) {
    clearScreen(COLOR_BLACK);
    lastStep = 0;
  } else {
    for (; lastStep <= step; lastStep++) {
      int startCol = col - lastStep;
      int endCol = col + lastStep;
      int width = 1 + endCol - startCol;
      
      // a color in this BGR encoding is BBBB BGGG GGGR RRRR
      unsigned int color = (blue << 11) | (green << 5) | red;
      
      fillRectangle(startCol, row+lastStep, width, 1, color);
      fillRectangle(startCol, row-lastStep, width, 1, color);
    }
  }
}  
*/

void
update_shape()
{
  screen_update_ball();
  screen_update_defense();
  screen_update_offense();
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}