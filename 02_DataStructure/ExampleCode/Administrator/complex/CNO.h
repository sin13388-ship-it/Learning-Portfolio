#ifndef CNO_HHHH_
#define CNO_HHHH_


//******************************************
//	Data structure definition
//******************************************

struct Complex_number
{
	float real ;
	float imaginary ; 		// µê¼Æ³¡
} ;

typedef struct Complex_number CNO ;


//******************************************
//	Method declaration
//******************************************

// method1 : Init
void complex_number_init(CNO * A,	float real_part, 	float imaginary_part) ;

// Method2 : add
// A + B = C
void  complex_number_add(CNO * A,CNO * B,CNO * C) ;


// Method3 : sub
// A - B = C
void  complex_number_sub(CNO * A,CNO * B,CNO * C) ;

// Method4: print
void  complex_number_print(CNO * A) ;


#endif
