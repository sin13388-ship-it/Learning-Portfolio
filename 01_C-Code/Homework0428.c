#include "C_Code_0428Example.h"
void multiple();
void print_square();
void square(int *);
void print_add_ten();
void add_ten(int *);
void print_arr();

void multiple(){
	
	int *ptra, *ptrb;
	
	int a=15, b=16;
	
	ptra=&a;
	ptrb=&b;
	printf("====Homework01====\n");
	
	printf("The result is %d \n", (*ptra) * (*ptrb));
	
	
}
void print_square(){
	printf("====Homework02====\n");
	int arr[5]={2,4,6,8,10};
	 square(arr);
	 int i;
	 for(i=0; i<5; i++) {
	 	printf("%4d", *(arr+i));
	 	
	 }
	printf("\n");	
	
}
void square(int *arr){
	int i;
	for(i=0; i<5; i++){		
		*(arr+i) *= *(arr+i);		
	}

}

void print_add_ten(){
	printf("====Homework03====\n");
	
	int arr[5]={34,76,33,42,76};
	int i;
	printf("Before====\n");
	for(i=0; i<5; i++) {
	 	printf("%4d", *(arr+i));
	 	
	 }
	 printf("\n");

	printf("After====\n");
	add_ten(arr);
	
	for(i=0; i<5; i++) {
	 	printf("%4d", *(arr+i));
	 	
	 }
	printf("\n");	
}

void add_ten(int *arr){
	int i;
	for(i=0; i<5; i++){		
		*(arr+i) += 10;		
	}

} 
void print_arr(){
	int arr[5]={10,20,30,40,50};
	int i;
	printf("====Homework04====\n");	
	int *ptr =&arr[4];	
	printf("%4d", *(ptr--));
	printf("%4d", *(ptr--));
	printf("%4d", *(ptr--));
	printf("%4d", *(ptr--));
	printf("%4d", *(ptr--));	
}


