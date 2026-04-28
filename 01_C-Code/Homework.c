#include "C_Code_0427Example.h"



void assign_pointer();
void count(int *);
void main_count();
void change_value();
void sum_odd_even();

void assign_pointer(){	
	float num=12.6f;
	float *ptr=&num;
	printf("===Homework1====\n");
	printf("value= %f, &num= %p , ptr=%p \n", num, &num, &ptr);
}

void main_count() {	
	int sum=0;
	int i =0;
	printf("===Homework2====\n");
	for(i=0; i<5; i++){
		count(&sum);
		printf("Call count() : %d 次, sum= %d \n", i+1,sum);		
		
	}	
}

void count(int *sum){	
	*sum +=1;
}

void change_value(){
	
	int AK[7]={23,39,77,74,25,82,91};
	int i=0;
	int index;
	printf("===Homework3====\n");
	printf("AK array = ");
	for (i=0; i<7; i++){
		printf("%d \t", AK[i]);
	}
	printf("\n");
	printf("請輸入要替換的位置 (從1 開始) :\n");
	scanf("%d",&index);
	fflush(stdin);
	printf("AK array = ");
	AK[index-1]=99;
		for (i=0; i< 7; i++){
		printf("%d \t", AK[i]);
	}
	printf("\n");

}

void sum_odd_even(){
	
	int sum_even=0;
	int sum_odd=0;
	
	int count=1;
	printf("===Homework4====\n");
	
	while (count <=100){
		if(count%2==0) sum_even+=count;
		else sum_odd+=count;
		
		count++;
	}
		printf("Odd = %d \t", sum_odd);
		printf("Even = %d \t", sum_even);		
}

