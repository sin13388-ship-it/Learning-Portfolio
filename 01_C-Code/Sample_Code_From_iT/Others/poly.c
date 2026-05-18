//
//   - command line : gcc -lm -o homework1 homework
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/******************************************************
	Configuration
******************************************************/

#define USING_MALLOC

#define MAX_N 10 


/******************************************************
	Function Declaration
******************************************************/

int solution1(void) ;   // knowledge as you know after class1.
int solution2(void) ;   // a better one.


/******************************************************
	Function: main
******************************************************/
int main()
{
 // we still don't know how to use ARRAY 	
 //solution1() ;

 solution2() ;


}



/******************************************************
	Function: solution2
  - return 0 if error
   
  - command line : gcc -lm -o homework1 homework
******************************************************/
int solution2(void) 
{
 int max_n ;
 int i ;
 
 int sum = 0 ;
 int x ;

 #ifndef USING_MALLOC
 	 int A[MAX_N] ; // array  ==> A[0], A[1] ,A[2] .... A[MAX_N-1]
	

	 if(max_n > MAX_N)
	 {
		printf("error!\n") ;
		return 0 ;
	 }

 #else
	 int *A;

	 printf("Please input Max n: ") ;
	 scanf("%d",&max_n) ;

	 // void * malloc( int size)
	 //
	 A = (int *)malloc(max_n *sizeof(int) ) ; 
	 if(A == NULL)
	 {
			printf("memory alloc error!\n") ;
			return 0 ;
	 }
  #endif 

 // let user input X
 printf("Please input X: ") ;
 scanf("%d",&x) ;

 for(i=0;i<max_n;i++)
 {
	 printf("Please input A%d: ",i) ;
	 scanf("%d",&(A[i])) ;
 
	 sum += (A[i] * pow(x,i)) ;	 	
 }

 printf("result = %d\n",sum) ;

#ifdef USING_MALLOC
	 free(A) ;
#endif	 
	 
 return 1 ;
}




/******************************************************
	Function: solution1
  - return 0 if error
  
******************************************************/


int solution1(void) 
{
 int max_n ;
 int x ;
 int sum ;
 
 int A0,A1,A2,A3,A4,A5,A6,A7,A8,A9 ;
 
 printf("Please input Max n: ") ;
 scanf("%d",&max_n) ;
 if( (max_n > MAX_N) || (max_n < 0))
 {
	printf("error!\n") ;
	return 0 ;
 }

 // let user input X
 printf("Please input X: ") ;
 scanf("%d",&x) ;

 //let user input A-n and start calculate summery
 if(max_n >= 0)
 {
 	printf("Please input A0: ") ;
 	scanf("%d",&A0) ;
 	
 	// <========================
 	// where is pow() ???  declaration? implementation?
 	sum = sum + A0*pow(x,0) ;
 }

 if(max_n >= 1)
 {
 	printf("Please input A1: ") ;
 	scanf("%d",&A1) ;
 	sum = sum + A1*pow(x,1) ;
 }

 if(max_n >= 2)
 {
 	printf("Please input A2: ") ;
 	scanf("%d",&A2) ;
 	sum = sum + A2*pow(x,2) ;
 }


 if(max_n >= 3)
 {
 	printf("Please input A3: ") ;
 	scanf("%d",&A3) ;
 	sum = sum + A3*pow(x,3) ;
 }


 if(max_n >= 4)
 {
 	printf("Please input A4: ") ;
 	scanf("%d",&A4) ;
 	sum = sum + A4*pow(x,4) ;
 }


 if(max_n >= 5)
 {
 	printf("Please input A5: ") ;
 	scanf("%d",&A5) ;
 	sum = sum + A5*pow(x,5) ;
 }


 if(max_n >= 6)
 {
 	printf("Please input A6: ") ;
 	scanf("%d",&A6) ;
 	sum = sum + A6*pow(x,6) ;
 }


 if(max_n >= 7)
 {
 	printf("Please input A7: ") ;
 	scanf("%d",&A7) ;
 	sum = sum + A7*pow(x,7) ;
 }


 if(max_n >= 8 )
 {
 	printf("Please input A8: ") ;
 	scanf("%d",&A8) ;
 	sum = sum + A8*pow(x,8) ;
 }


 if(max_n >= 9)
 {
 	printf("Please input A9: ") ;
 	scanf("%d",&A9) ;
 	sum = sum + A9*pow(x,9) ;
 }

 printf("result = %d\n",sum) ;
 return 1 ;
}

