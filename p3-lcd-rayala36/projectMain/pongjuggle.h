#ifndef pattern_included
#define pattern_included

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

void drawDiamond(int cCol, int cRow, int size, unsigned int color);

void draw_ball(int col, int row, unsigned short color);
void screen_update_ball();

void draw_defense(int col, int row, unsigned short color);
void screen_update_defense();

void draw_offense(int col, int row, unsigned short color);
void screen_update_offense();

void update_shape();

void scoreJT(int score);
#endif
