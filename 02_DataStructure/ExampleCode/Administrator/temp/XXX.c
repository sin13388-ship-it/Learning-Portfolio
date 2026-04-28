int power(int x, int n)
{
 int sum = 1 ;
 int i ;

 for(i=0;i<n;i++)
 {
	sum = sum*x ;
 }

 return sum ;
}


int power(int x, int n)
{
 if(n == 0)
	return 1 ;
 else
 {
	return x * power(x,n-1) ;
 }

}




b =      1010 1010
mask =   1111 0111   &  ==> 0xF7
================================
         1010 0010
         
b =      1010 1010
mask =   0000 1000   | ==> 0x08
================================
	       1010 1010
         
         
if (number > 6)
{
	if (number < 12) 
	{
		printf("You're close!\n");
	}
	else
	{ 
		printf("Sorry, you lose a turn!\n"); 
	}        
}         








int a = 5 ;
while(a >= 1)
{
 	printf(xxxx"\n") ;
 	a-- ;
}


while(1)
{
 if(get_message() )
 {
 		process_message() ;
 
 }
 else
 {
 		enter_idle_mode() ;
 }

}






char key ;

if(key == 'A')
{


}
else if(key == 'B')
{

}
else if(key == 'C')
{

}
else if(key == 'D')
{

}
else if(key == 'D')
{

}
else if(key == 'E')
{

}
else if(key == 'F')
{

}
...
else
{
	// default
	
}



switch(key)
{
	case 'A':
		...
		...
	case 'B':
		..
		break ;

	case 'C':
		..
		break ;
		
..
	case 'Z':
		..
		break ;

	default:
		..
		.. 
		break ;
	
}





long fac ( int n )
{
     if (n <= 1)  
				return 1;
     
     return  n*fac(n-1) ;
}

main()
{
	
	fac(3) = 6 ;
	
}

1.
fac-L1(n= 3)
{
    
     return  3*2 ;
	
}

2.
fac-L2(n=2)
{
     return  2*1 ;
}

3.
fac-L3(n=1)
{
     if (n <= 1)  
				return 1;
}








#include <stdio.h>
#define IMIN(N,M) (((N)<(M))? (N) : (M))

int main(void)
{
  int x=100,y=50;
    printf("The lesser of %d and %d is %d.\n",
            x, y,/*IMIN(x,y) ==> */  (((tt)<(y))? (tt) : (y)) );
 return 0;
}


#include <stdio.h>
#define SQUARE(X) ((X)*(X)  .......... )
#define PR(X)   printf("The result is %d.\n", X)
int main(void)
{
     int x = 4;
     int z;

     z = SQUARE(x);  ==> x*x
     PR(z);
     z = SQUARE(2);   ==> 2*2
     PR(z);
     PR(SQUARE(x+2)); (x+2)*(x+2)  
     PR(100/SQUARE(2));  100/(2*2)  ==> 200
     printf("x is %d.\n", x);
     PR(SQUARE(++x));   <== ++x*++x 
     printf("After incrementing, x is %x.\n", x);
     return 0;
}


int SQUARE2(int x)
{
	
	....
}



















