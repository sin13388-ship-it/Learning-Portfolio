#include "poly.h"
#include "stdio.h" 

/*
struct poly
{
	int degree ;  //A(x) = a100.X^50 + 1  ===>  degree = 50
	float coef[MAXDEGREE+1] ;
} ;
*/

/***********************************************************
	Method:poly_init
		return 0 if degreee > MAXDEGREE
***********************************************************/
int poly_init(POLY * A, int degree,const float an[]) 
{
 int i ;	
	
 if(degree > MAXDEGREE)		// error
 	return 0 ;
 	
 A->degree = degree ; 	
 
 for(i=0;i<=degree;i++)
 {
 		A->coef[i] = an[i] ;
 }
 
 for(i=degree+1;i<=(MAXDEGREE);i++)
 		A->coef[i] = 0 ;
 
}

/***********************************************************
	Method:poly_print
***********************************************************/
void poly_print(POLY * A) 
{
 int i ;

 for(i=0;i<=(A->degree);i++)
 {
 	  if(A->coef[i] == 0)		// an = 0 <== 此項可以不用顯示
 	  	continue ;
 	
 	  if(((A->degree) - i) == 0)
 	  	printf("%5.2f",A->coef[i]) ;			// a0  <== 不用顯示X^0
 	  else
 	  {
 	  	// e.g.
 	  	// poly = coef[0].X^4 + coef[1].X^3 + coef[2].X^2 + coef[3].X^1 + coef[4]
 	  	//             ?   ??        ?   ??
 	  	
			printf("%5.2f.X^%d ",A->coef[i],(A->degree) - i) ;	
 		}
 		
 		if(i < A->degree)
 			printf("+ ") ;
 }
 printf("\n\n") ;

 	
}


/***********************************************************
	Method:poly_equal
***********************************************************/
// return 1 if equal, else return 0
int poly_equal(POLY * A, POLY * B) 
{
 int i ;
 	
 if(A->degree != B->degree)	
 {
 	 		return 0 ;
 } 		

 for(i=0;i<=(A->degree);i++)
 {
 		if(A->coef[i] != B->coef[i])
 		{
 			return 0 ;
 		}
 } 	
	
 return 1 ;
}


/***********************************************************
	Method:poly_set
***********************************************************/
// set A = B
void poly_set(POLY * A, const POLY * B) 
{
 poly_init(A, B->degree, B->coef) ;
}


/***********************************************************
	Method:poly_add
***********************************************************/
// C = A + B
void poly_add(POLY * A, POLY * B, POLY * C) 
{
 int i ;
 int degree_offset ;			// A與B這兩個多項式， 最高degree的差值

 POLY * small_poly ;			// 指到degree比較小的多項式
 POLY * large_poly ;			// 指到degree比較大的多項式
 
 if(A->degree > B->degree)	
 {
 		// A的degree較高
 		
 		degree_offset = A->degree - B->degree ;	
 		large_poly = A ;		
 		small_poly = B ;
 }
 else
 {
 		// B的degree較高

 		degree_offset = B->degree - A->degree ;	
 		large_poly = B ;
 		small_poly = A ;
 	} 		

 // 先將多項式C設定為與large_poly相等
 poly_set(C,large_poly) ;

 // 只要對 small_poly 有的項次做相加
 for(i=0;i<=(small_poly->degree);i++)
 {
 			// 例如：
 			// large_poly = coef[0].X^4 + coef[1].X^3 + coef[2].X^2 + coef[3].X^1 + coef[4]
 			// small_poly =                             coef[0].X^2 + coef[1].X^1 + coef[2]
 			//
 			C->coef[i+degree_offset] = small_poly->coef[i] + large_poly->coef[i+degree_offset] ;
 } 		
 
// for(i=(large_poly->degree)+1;i<=(MAXDEGREE);i++)
// 		C->coef[i] = 0 ;
 
}

