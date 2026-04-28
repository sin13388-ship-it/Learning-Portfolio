#include "button.h"

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
 if(check_coordinate(left, top) == 0 || 
    check_coordinate(right, bottom) == 0) 
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
