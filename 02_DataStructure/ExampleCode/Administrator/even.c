#include <stdio.h>

main()
{
 int a ; 
 int b[] = {1,2,3,4}; 

 printf("PLease input a number:\n") ;
 scanf("%d",&a) ;

 // algorithm 1
 if( (a % 2) == 0)  // it's an even
 {
		printf("this is an even number\n") ;
 }
 else
		printf("this is a odd number\n") ;
	
 // algorithm 2
 if( (a & 0x0001) == 0)  // it's an even
		printf("this is an even number\n") ;
 else
		printf("this is a odd number\n") ;

}


