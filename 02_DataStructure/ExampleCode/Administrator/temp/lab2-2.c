#include <stdio.h>

int main(void)
{
  int a = -123;
  float b = 23.45;
  int c = 65535;
  double d = 12345.6789;
  int e = 0x1234;
  
  //a = a*-1;
  // 1.
  printf("-%7d\n",a*(-1) ) ;
  
  // 2
  printf("%13.4f\n",b) ;
  
  printf("%8d\n",c) ;
  printf("%13.4f\n",d) ;
  printf("0x%6x\n",e) ;
  

  return 0;
}
