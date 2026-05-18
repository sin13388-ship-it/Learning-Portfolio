
#include <stdio.h>

#define LCD_WIDTH 320
#define LCD_HEIGHT 240


int main()
{

	
 // information of button
 int left, top, W, H ;
 int right, bottom ;

 // coorinate user touched
 int X,Y ;


 printf("please input button location (L,T,W,H ) : ") ;
 scanf("%d,%d,%d,%d",&left, &top, &W, &H ) ;

 right = left + W - 1 ;
 bottom = top + H - 1 ;

 // check button boundary:
 
 if( (left < 0    || left >= LCD_WIDTH)  ||
     (top < 0     || top  >= LCD_HEIGHT) ||
	   (right < 0   || right >= LCD_WIDTH)  ||
     (bottom < 0  || bottom  >= LCD_HEIGHT) )
 {
	printf("button boundary error! \n") ;
	return 0 ;
 }
 
 while(1)
 {

	 printf("\nPlease input X,Y you touched:") ;
	 scanf("%d,%d",&X, &Y) ;
	
 	 // exit once user intput X=0 and Y=0!
	 if(X == 0 && Y == 0)
	 {
		printf("Bye!\n") ;
		break ;
	 }
	 
	 if( (X >= left && X <= right)  &&
	     (Y >= top && Y <= bottom) )
	 {
		printf("OKOK!\n") ;
	 }
	 else
	 {
		printf("out of button!\n") ;
	 }

 } 
}


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
