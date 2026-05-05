#include "C_Code_0505Example.h"
int decimalToBinary(int);
void pointers();
void get_array_elements_with_pointers2();
void struct_assignment();
void time_elapse();
int main(){
	
	//printf("%d (dec) = %d (bin) \n", 121,decimalToBinary(121));
	//pointers();
	//get_array_elements_with_pointers();
	//get_array_elements_with_pointers2();
	//structure_exercise();
	//structure_size();
	//structure_initialize();
	//define_struct_also_create();
	//struct_assignment();
	//struct_array_and_its_size();
	//nested_structure();
	//structure_assignment_using_stdin();
	//nested_struct_now();
	//student_data();
	//structure_pointer();
	structure_pointer_get_value();

	getchar();
	return 0;
}

int decimalToBinary(int dec){
	
	int rem;
	int times=1;
	int n =dec;
	int i=1;
	int binary=0;
	while(n!=0){		
		rem = n%2;
		printf("loop %d, rem =%d \n", i++, rem );
		n /=2;
		binary +=rem *times;
		times *=10; //shift 10
	}
	return binary;	
}

void pointers(){
	//num[x] == &num[x]	
	int num[3][4];
	printf("num=%p\n", num);
	printf("&num=%p\n", num);	
	printf("num[0]=%p\n", num[0]);
	printf("num[1]=%p\n", num[1]);
	printf("num[2]=%p\n", num[2]);	
	printf("&num[0]=%p\n", &num[0]);
	printf("&num[1]=%p\n", &num[1]);
	printf("&num[2]=%p\n", &num[2]);	
}
void get_array_elements_with_pointers(){	
		int num[3][4] =
		{
			{12,23,43,18},
			{43,22,16,14},
			{31,19,13,28}			
		};	
	int m=0, n=0;	
	for(m=0; m<3; m++){
		for (n=0; n<4; n++){
			//*(num + m) 雖然在語法上是「取值」，但結果會變成指向 num[m][0] 的指標
			//*(*(num + m) + n): 等同於 num[m][n]。先找到第 m 列的起點指標，往後移動 n 個整數單位，最後再取值。
			printf("num[%d][%d]=%d, address =%p \n", m,n, *(*(num+m)+n),*(num+m)+n);
		}
	}
}
void get_array_elements_with_pointers2(){	
		int arr[2][5] =
		{
			{1,2,3,4,5},
			{5,6,7,8,9}	
		};	
	int m=0, n=0;	
	for(m=0; m<2; m++){
		for (n=0; n<5; n++){
			printf("arr[%d][%d]=%d, address =%p \n", m,n, *(*(arr+m)+n),*(arr+m)+n);
		}
	}
}



