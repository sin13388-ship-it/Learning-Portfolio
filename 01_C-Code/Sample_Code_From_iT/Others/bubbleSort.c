#include <stdio.h> /* Bubble Sort */ 

main() 
{ 
 int data[50]; 
 int i,j,n,temp; 

 printf("Please input integer number you want to sort:");
 scanf("%d" ,&n); 
 printf("\n"); 

 if (n > 49) 
 { 
	printf("number should be less than 49\n"); 
	return; 
 } 

 for (i = 0;i < n;i++) 
 { 
	printf("input data[%d]=", i); 
	scanf("%d", &data[i]); 
 } 

 for (i=1; i <= n; i++) 
 { 
	for (j = n; j > i; j--) 
	{ 
		if (data[j-1] > data[j]) 
		{ 
			temp = data[j-1]; 
			data[j-1] = data[j]; 
			data[j] = temp; 
		} 
	} 
 } 

 printf("\nSorting result: \n"); 
 for(i = 1; i <= n; i++) 
		printf("%d ", data[i]); 

		
} 



