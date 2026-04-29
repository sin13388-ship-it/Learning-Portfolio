#include <stdio.h>

void swap(int *a, int *b)
{ 
  int t=*a; *a=*b; *b=t; 
}
 
void quicksort(int arr[],int beg,int end)
{
	if (end  >= beg + 1) 
  {
  		int piv = arr[beg], k = beg + 1, r = end;
 
			while (k < r) 
    	{
      			if (arr[k] < piv) 
        			k++;
      			else 
        			swap(&arr[k], &arr[r--]);
    	}
		
			if (arr[k] < piv)
			{
 
				swap(&arr[k],&arr[beg]);
 
				quicksort(arr, beg, k);
				quicksort(arr, r, end);			
			}
			else 
			{
				if (end - beg == 1)
  				return;
 
				swap(&arr[--k],&arr[beg]);
				quicksort(arr, beg, k);
				quicksort(arr, r,   end);			
			}
  	}
 
}



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
	
	quicksort(data,0,DATA_NO-1) ;
	
	printf("\nAfter Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	
}