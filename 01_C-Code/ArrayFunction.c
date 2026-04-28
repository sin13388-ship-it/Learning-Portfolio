#include "C_Code_0428Example.h"

void update(int[], int);
void array_update();
void bits_shfiter();
void array_and_pointers_and_size();
void array_and_pointers_and_retrieve();
void array_and_pointers_and_retrieve2();
void evaluate_sum_with_pointer();
void string_pointers();
void find_maximum();
int *maximum(int *, int);

int main(){	
	//array_update();	
	//bits_shfiter();
	//array_and_pointers_and_size();
	//array_and_pointers_and_retrieve2();
	//evaluate_sum_with_pointer();
	//string_pointers();
	find_maximum();
}

void array_update(){	
	int i;
	int arr[6]={23,46,37,57,42,9};
	printf("Before update: \n");
	for (i=0; i<6; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");
	update(arr,6);
	printf("After update: \n");
	for (i=0; i<6; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n");	
}
void update(int arr[], int n)
{
	/* 陣列被傳入時會被退化成指標，
	* 所以要連陣列的長度一起傳入*/ 

	int i;
	for (i=0; i<n; i++){
		if(arr[i]%2==1){
			arr[i]++;
		}
		else{
			arr[i]--;
		}
	}	
}

void bits_shfiter(){
	unsigned char ch=53;
	unsigned char ix=5;
	ch=ch<<1;
	printf("ch=%x\n",ch);
	ch=ch<<1;
	printf("ch=%x\n",ch);
	ch=ch<<1;
	printf("ch=%x\n",ch);
	ch=ch>>1;
	printf("ch=%x\n",ch);
	ch=ch>>1;
	printf("ch=%x\n",ch);
	ix=ix<<5;
	printf("ix<<5=%X\n",ix);
	ix=ix>>5;
	printf("ix>>5=%x\n",ix);	
}
void array_and_pointers_and_size(){	
	/* 不同型態的大小，所暫的空間也不一樣
	* 位址的級距也不一樣 
	*/
	int i, AB[5]={32,16,35,65,77};
	char AC[5]={65,66,68,69,70};
	for (i=0; i<5; i++){
		printf("&AB[%d]=%p\n", i, &AB[i]);
	}
	printf("=====================\n");
	for (i=0; i<5; i++){
		printf("&AC[%d]=%p\n", i, &AC[i]);
	}	
}
void array_and_pointers_and_retrieve(){	
	int score[4]={75,88,66,57};
	printf("score[0]=%d, *(score+0)=%d\n", score[0], *(score+0));
	printf("score[1]=%d, *(score+1)=%d\n", score[1], *(score+1));
	printf("score[2]=%d, *(score+2)=%d\n", score[2], *(score+2));
	printf("score[3]=%d, *(score+3)=%d\n", score[3], *(score+3));
} 
void array_and_pointers_and_retrieve2(){	
	/*Array名稱+1 = pointer +1  */	
	
	int AB[5]={13,15,17,19,11};
	int i, sum=0;
	int *ptr;
	ptr=AB+1;
	printf("*ptr=%d\n", *ptr); //15
	printf("*(ptr+1)=%d\n", *(ptr+1)); //17
	printf("*(ptr-1)=%d\n", *(ptr-1)); //15
	printf("*(ptr+2)=%d\n", *(ptr+2)); //19
} 
void evaluate_sum_with_pointer(){	
	/*
		*(ptr++) = *ptr++ =*ptr 取值後, ptr++; 
	*/		
	int IOTA[6]={1,2,4,6,8,10};
	int *ptr =IOTA;
	int sum=0;
	int i=0;
	while(i<6){
		sum +=*(ptr++);
		i++;
	}
	printf("sum=%d\n", sum);
}

void string_pointers(){
	
	char name[20];
	char *ptr ="How are you";
	printf("What's your name ?\n");
	fgets(name,20,stdin);
	name[strcspn(name,"\n")]=0;
	printf("Hi %s \n", name);
	puts(ptr);
	
}

void find_maximum(){
	
	int array[6]={23,37,58,97,75,92};
	
	int i, *ptr;
	
	printf("Array AB[]= ");
	for(i=0; i<6; i++){
		printf("%d\t", array[i]);
	}
	printf("\n");
	ptr=maximum(array, 6);	
	printf("The maximum is %d\n", *ptr);	
	
}



int *maximum(int *arr, int length){
	
	int *max ;
	max=arr;
	
	int i=0;
	for(i=1; i<length; i++){
		if (*max < *(arr+i ) )*max=*(arr+i);
	}
	return max;
	
}



