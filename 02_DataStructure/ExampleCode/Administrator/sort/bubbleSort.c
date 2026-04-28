#include <stdio.h>

enum {FALSE=0,TRUE} ;

/************************************************
	Function:bubble
************************************************/
void bubbleSort(int x[], int n)
{
  int hold, j, pass;
  int switched = TRUE;

  for (pass=0; pass < n-1 && switched == TRUE; pass++)
  {
    /*outer loop controls the number of passes          */
    switched = FALSE; 	/* initially no interchanges have */
                      	/* been made on this pass         */
    for (j = 0; j < n-pass-1; j++)
    {
	      /* inner loop governs each individual pass */
	      if (x[j] > x[j+1])
	      {
	        /* elements out of order */                
	        /* an interchange is necessary */
	        switched = TRUE;
	        hold = x[j];
	        x[j] = x[j+1];
	        x[j+1] = hold;  
	      } /* end if */
    }  

  } /* end for */

} /* end bubble */


/************************************************
	Function: main
************************************************/
#define DATA_NO 10

main()
{
	int i ;
	int data[DATA_NO] = {23,57,34,87,12,66,15,14,90,26} ;
	
	printf("\nBefore Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	bubbleSort(data,DATA_NO) ;
	
	printf("\nAfter Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	
}
