#include <stdio.h>

main()
{

 int a = -123;
 float b = 23.45;
 int c = 65535 ;
 double d = 12345.6789;
 int e = 0x1234 ;

 printf("\n") ;
 printf("-%8d\n",-1*a) ;
 printf("%14.4f\n",b) ;
 printf("%9d\n",c) ;
 printf("%14.4f\n",d) ;
while(1)
 printf("0x%7x\n",e) ; 

 getchar() ;
}
