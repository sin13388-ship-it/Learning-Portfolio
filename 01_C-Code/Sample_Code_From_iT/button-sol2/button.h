#ifndef BUTTON_HHHHH_
#define BUTTON_HHHHH_


#include <stdio.h>

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

// declaration
int check_coordinate_in_LCD(int x, int y) ;

int get_button_boundary(int * L,int * T, int * W, int *H) ;

int check_coordinate_in_button(int x,int y,int left,int top,int right,int bottom) ;


#endif
