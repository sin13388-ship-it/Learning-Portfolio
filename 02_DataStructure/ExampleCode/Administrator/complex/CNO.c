#include <stdio.h>
#include "CNO.h"

/**************************************************************
	Method:complex_number_init
// method1 : Init
**************************************************************/
void complex_number_init(CNO * A,	float real_part, 	float imaginary_part) 
{
 A->real = real_part ;
 A->imaginary = imaginary_part ;
}


/**************************************************************
	Method:complex_number_add
// A + B = C
**************************************************************/
void  complex_number_add(CNO * A,CNO * B,CNO * C) 
{
 C->real = A->real + B->real ;	
 C->imaginary = A->imaginary + B->imaginary ;	
}


/**************************************************************
	Method:complex_number_sub
// A - B = C
**************************************************************/
void  complex_number_sub(CNO * A,CNO * B,CNO * C) 
{
 C->real = A->real - B->real ;	
 C->imaginary = A->imaginary - B->imaginary ;	
}

/**************************************************************
	Method:complex_number_print

**************************************************************/
void  complex_number_print(CNO * A) 
{
 printf("A = %5.2f + %5.2fi\n",A->real, A->imaginary) ;
	
}



/**************************************************************
	Method: Private Function

**************************************************************/

int complex_my_private_fun1(void)
{
	
	
}

static int complex_my_private_fun2(void)
{
	
}


/**************************************************************
	Method: Private Attribute
**************************************************************/
int Complex_VAR1 ;

static int Complex_VAR2 ;
