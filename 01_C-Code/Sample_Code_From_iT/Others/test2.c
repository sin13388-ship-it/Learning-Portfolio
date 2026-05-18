#include <stdio.h>

main()
{
 const float PI = 3.1415926 ;	
 float r ; // for input
 float result ;
 
 printf("please input R :") ;
 scanf("%f",&r) ;
 
 // calculate C
 result = 2 * PI * r ;
 
 // output result
 printf("result = %f", result) ;
		
}

