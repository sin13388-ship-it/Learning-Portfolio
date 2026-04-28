#include "CNO.h"
#include <stdio.h>

main()
{
 // define A = 2.3+4.6i ,B = 56.2 + (-12.34)i
 CNO A, B, C ;
 
 complex_number_init(&A,2.3f,4.6f) ;
 complex_number_init(&B,56.2f,-12.34f) ;
 
 // C = A + B
 complex_number_add(&A,&B,&C) ;
 
 // print C 
 complex_number_print(&C) ; 
 
 // C = A - B
 complex_number_sub(&A,&B,&C) ;
 
 // print C 
 complex_number_print(&C) ; 
 
 /*
 {
 	extern int complex_my_private_fun1(void) ;
  complex_my_private_fun1() ;  // <== compile warnning
  
  complex_my_private_fun2() ;   // <== compile error!!!
 }
 
 {
extern int Complex_VAR1 ;
Complex_VAR1 = 0 ;


extern int Complex_VAR2 ; 	
 Complex_VAR1 = 0 ; // NG!!!	
}
*/ 
}

