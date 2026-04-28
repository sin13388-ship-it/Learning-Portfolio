#include <stdio.h>
#include <stdlib.h>


void _2wayMerge(int array[], int low, int mid, int high)
{
	int i, k;
	int *temp = (int *) malloc((high-low+1) * sizeof(int)); //申請空間，使其大小為兩個已經排序序列之和，該空間用來存放合併後的序列
	int begin1 = low;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = high;
 
	//比較兩個指針所指向的元素，選擇相對小的元素放入到合併空間，並移動指針到下一位置
	for (k = 0; begin1 <= end1 && begin2 <= end2; ++k)  
		if(array[begin1]<array[begin2])
			temp[k] = array[begin1++];
		else
			temp[k] = array[begin2++];	
			
	//若第一個序列有剩餘，直接拷貝出來粘到合併序列尾
	while(begin1<=end1) 
		temp[k++] = array[begin1++];
		
	//若第二個序列有剩餘，直接拷貝出來粘到合併序列尾	
	while(begin2<=end2) 
		temp[k++] = array[begin2++];
	
	//將排序好的序列拷貝回數組中	
	for (i = 0; i < (high-low+1); i++) 
		array[low+i] = temp[i];
	free(temp);
}




/************************************************
	Function: main
************************************************/
#define DATA_NO 10

main()
{
	int i ;
	int data[DATA_NO] = {12,23,34,57,87, /*兩段排過序的data*/  14,15,26,66,90} ;
	
	printf("\nBefore Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	_2wayMerge(data,0,4,DATA_NO-1) ;
	
	printf("\nAfter Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	
}
