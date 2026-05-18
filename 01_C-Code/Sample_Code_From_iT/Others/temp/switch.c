#include <stdio.h>

main()
{
unsigned char ch,cch ;

while ((ch = getchar()) != '#')
{
    cch = toupper(ch);
    switch (cch)
    {
      case 'A' :  
      						printf("AAA\n") ;
                  break;
      case 'E' :  printf("EEE\n") ;
                  break;
      case 'I' :  printf("III\n") ;
                  break;
      case 'O' :  printf("OOO\n") ;
                  break;
      case 'U' :  printf("UUU\n") ;
                  break;
      default :   printf("XXX %d\n",cch) ;
      
      						break;
    }                                  /* end of switch  */
}


}