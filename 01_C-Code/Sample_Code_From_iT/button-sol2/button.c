
#include "button.h"

/****************************************************
	return 0 if error!
****************************************************/
// definition
int check_coordinate_in_LCD(int x, int y) 
{
 if(x < 0 || x >= LCD_WIDTH)
	return 0 ;

 if(y < 0 || y >= LCD_HEIGHT)
	return 0 ;

 return 1 ;
}


/****************************************************
	return 0 if error!
****************************************************/
int get_button_boundary(int * L,int * T, int * W, int *H) 
{
 int right, bottom ;

 // please think about why we don't use "&" when calling scanf()
 //
 printf("please input button location (L,T,W,H ) : ") ;
 scanf("%d,%d,%d,%d",L, T, W, H ) ;

 right = (*L) + (*W) - 1 ;
 bottom = (*T) + (*H) - 1 ;

 // check button boundary:
 if(check_coordinate_in_LCD((*L), (*T)) == 0 || 
    check_coordinate_in_LCD(right, bottom) == 0) 
 {
	return 0 ;
 }

 return 1 ;
}



/****************************************************
	return 0 if error!
****************************************************/
int check_coordinate_in_button(int x,int y,int left,int top,int right,int bottom) 
{
	 if(check_coordinate_in_LCD(x,y) == 0)
	 	return 0 ;
	
	 if( (x >= left && x <= right)  &&  (y >= top && y <= bottom) )
	     	return 1 ;
	 else
	 			return 0 ;   	
	
}
