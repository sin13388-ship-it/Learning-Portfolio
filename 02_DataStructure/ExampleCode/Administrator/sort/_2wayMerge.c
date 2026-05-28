#include <stdio.h>
#include <stdlib.h>


void _2wayMerge(int array[], int low, int mid, int high)
{
	int i, k;
int *temp = (int *) malloc((high-low+1) * sizeof(int)); // allocate space equal to the sum of two sorted subarrays; this holds the merged sequence
	int begin1 = low;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = high;
 
	// compare the elements pointed by two pointers, choose the smaller one to put into merge space, and advance the pointer
	for (k = 0; begin1 <= end1 && begin2 <= end2; ++k)  
		if(array[begin1]<array[begin2])
			temp[k] = array[begin1++];
		else
			temp[k] = array[begin2++];		
		
	// if the first sequence has remaining elements, copy them directly to the end of merged sequence
	while(begin1<=end1) 
		temp[k++] = array[begin1++];
		
	// if the second sequence has remaining elements, copy them directly to the end of merged sequence
	while(begin2<=end2) 
		temp[k++] = array[begin2++];
	
	// copy the sorted merged sequence back into the original array
	for (i = 0; i < (high-low+1); i++) 
		array[low+i] = temp[i];
	free(temp);
}




/************************************************
	Function: main
************************************************/
#define DATA_NO 10

int main()
{
	int i ;
	//資料必須是經過排序的
	int data[DATA_NO] = {12,23,34,57,87, /*sorted data*/  14,15,26,66,90} ;
	
	
	printf("\nBefore Sorting:\n") ;
	//for(i=0;i<DATA_NO;i++)
	for(i=0;i<7;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	//_2wayMerge(data,0,4,DATA_NO-1) ;
	_2wayMerge(data,0,4,6) ;

	
	printf("\nAfter Sorting:\n") ;
	//for(i=0;i<DATA_NO;i++)
	for(i=0;i<7;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	return 0;
}
