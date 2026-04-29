#include <stdio.h>


// selection sort function module in C
void selectionSort(int data[], int count)
{
        int i, j, min, temp;
        for (i = 0; i < count - 1; i++) 
        {
                /* find the minimum */
                min = i;
                for (j = i+1; j < count; j++) 
                {
                    if (data[j] < data[min]) 
                    {
                        min = j;
                    }
                }
                /* swap data[i] and data[min] */
                temp = data[i];
                data[i] = data[min];
                data[min] = temp;
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
	
	selectionSort(data,DATA_NO) ;
	
	printf("\nAfter Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	
}
