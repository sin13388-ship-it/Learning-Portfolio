#include <string.h>
#include <stdio.h>

unsigned char reverse_bit(unsigned char c) ;


main()
{
 char string[10] = "ABCDEFGHI" ;
 int i ;
 char temp ;

 int length = strlen(string) ;
 
  
 for(i=0;i<(length/2);i++)
 {
	temp = string[i] ;
	string[i] = string[length-1-i] ;
	string[length-1-i] = temp ;
 }

 printf("%s\n",string) ;
 
 {
 	unsigned char c = 0xF0 ;	
 	
 	printf("reverse bit : 0x%x \n",reverse_bit(c)) ;
 	
 }
 
 
}


unsigned char reverse_bit(unsigned char c)
{
/*	
  int i;
  unsigned char newc = 0x00;

	for(i=0;i<8;i++)
	{
		if( c & (0x1 << i) )
			newc |= (0x1 << (7-i)) ;
	}
	
	return newc ;
	*/
	
        int i;
        unsigned char newc = 0x00;

        for (i = 0; i < 8; i++) 
        {
                newc |= (c & 1);
                newc <<= 1;
                c >>= 1;
        }

        return newc;
        
}

