
#include "button.h"

/****************************************************
	return 0 if error!
****************************************************/
// definition
int check_coordinate(int x, int y) 
{
 if(x < 0 || x >= LCD_WIDTH)
	return 0 ;

 if(y < 0 || y >= LCD_HEIGHT)
	return 0 ;

 return 1 ;
}
