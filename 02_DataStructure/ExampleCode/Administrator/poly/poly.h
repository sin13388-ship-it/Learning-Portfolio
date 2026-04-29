#ifndef POLY_HHHH_
#define POLY_HHHH_


// limitation
#define MAXDEGREE 50


/***********************************************************
	Data Structure definition
***********************************************************/

struct poly
{
	int degree ;  //A(x) = a100.X^50 + 1  ===>  degree = 50
	float coef[MAXDEGREE+1] ;
} ;

typedef struct poly POLY ;


/***********************************************************
	Interface Declaration
***********************************************************/

int poly_init(POLY * A, int degree, const float an[]) ;

void poly_print(POLY * A) ;

// return 1 if equal, else return 0
int poly_equal(POLY * A, POLY * B) ;

// set A = B
void poly_set(POLY * A, const POLY * B) ;

// C = A + B
void poly_add(POLY * A, POLY * B, POLY * C) ;

#endif

