#include <stdio.h>
#include "poly.h"

main()
{
	// A(x) = 10.x^5 + 1.x^2 + 3
	POLY A ;
	int A_degree = 5 ;
	
	//   0, 1, 2 ,3, 4, 5   //  <== array access¶¶§Ç 
	//   5, 4, 3, 2, 1, 0   //   <== N¦¸¤è
	//  a[5-0], a[5-1], a[5-2], a[5-3], a[5-4], a[5-5]
	float A_an[] = {10,0,0,1,0,3} ;   

	POLY B ;
	
	// C(x) = 15.x^10 + 6.x^6 + 6.x^2 + 8
	POLY C ;
	int C_degree = 10 ;
  float C_an[] = {15,0,0,0,6,0,0,0,6,0,8} ;
  											   //{10,0,0,1,0,3}
  POLY D ;
	
	poly_init(&A,A_degree,A_an) ;
	printf("poly A = \n") ;
	poly_print(&A) ;
	
	// set B = A
	poly_set(&B,&A) ;
	printf("poly B = \n") ;
	poly_print(&A) ;
	
	// test A == B ?
	if(poly_equal(&A,&B)== 1)
		printf("A = B\n\n") ;
	else
		printf("A != B\n\n") ;

  // init C
	poly_init(&C,C_degree,C_an) ;
	printf("poly C = \n") ;
	poly_print(&C) ;

	// test A == C ?
	if(poly_equal(&A,&C)== 1)
		printf("A = C\n\n") ;
	else
		printf("A != C\n\n") ;

	// D = A + C
	poly_add(&A,&C,&D) ;
	printf("D = A + C = \n") ;
	poly_print(&D) ;
	
	
}

