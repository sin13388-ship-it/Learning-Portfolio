#include <stdio.h>
#include <stdlib.h>

/************************************************
	Function: _2wayMerge
************************************************/

void _2wayMerge(int array[], int low, int mid, int high)
{
	int i, k;
	int *temp = (int *) malloc((high-low+1) * sizeof(int)); //�ӽЪŶ��A�Ϩ�j�p����Ӥw�g�ƧǧǦC���M�A�ӪŶ��ΨӦs��X�᪺֫�ǦC
	int begin1 = low;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = high;
 
	//�����ӫ��w�ҫ��V�������A��ܬ۹�p��������J��X�֪Ŷ��A�ò��ʫ��w��U�@��m
	for (k = 0; begin1 <= end1 && begin2 <= end2; ++k)  
		if(array[begin1]<array[begin2])
			temp[k] = array[begin1++];
		else
			temp[k] = array[begin2++];	
			
	//�Y�Ĥ@�ӧǦC���Ѿl�A���������X���ߨ�X�֧ǦC��
	while(begin1<=end1) 
		temp[k++] = array[begin1++];
		
	//�Y�ĤG�ӧǦC���Ѿl�A���������X���ߨ�X�֧ǦC��	
	while(begin2<=end2) 
		temp[k++] = array[begin2++];
	
	//�N�ƧǦn���ǦC�����^�Ʋդ�	
	for (i = 0; i < (high-low+1); i++) 
		array[low+i] = temp[i];
	free(temp);
}



/************************************************
	Function: merge_sort
************************************************/


void merge_sort(int array[], unsigned int first, unsigned int last)
{
	int mid = 0;
	if(first<last)
	{
		mid = (first+last)/2;
		merge_sort(array, first, mid);
		merge_sort(array, mid+1,last);
 		_2wayMerge(array,first,mid,last);
	}
}



/************************************************
	Function: main
************************************************/
#define DATA_NO 10

int main()
{
	int i ;
	int data[DATA_NO] = {23,57,34,87,12,66,15,14,90,26} ;
	
	printf("\nBefore Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	merge_sort(data,0,DATA_NO-1) ;
	
	printf("\nAfter Sorting:\n") ;
	for(i=0;i<DATA_NO;i++)
		printf("%d  ", data[i]) ; 
	printf("\n") ;
	
	return 0;
	
}

