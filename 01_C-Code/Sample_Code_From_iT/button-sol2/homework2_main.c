#include "button.h"


int main()
{
 // information of button
 int left, top, W, H ;
 int right, bottom ;

 // coorinate user touched
 int X,Y ;
 
 if(get_button_boundary(&left,&top,&W,&H) == 0)
 {
	printf("button boundary error! \n") ;
	return 0 ;
 }

 right = left + W - 1 ;
 bottom = top + H - 1 ;


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
	 
	 if(check_coordinate_in_button(X,Y,left,top,right,bottom) )
	 {
		printf("OKOK!\n") ;
	 }
	 else
	 {
		printf("out of button!\n") ;
	 }

 }
}
