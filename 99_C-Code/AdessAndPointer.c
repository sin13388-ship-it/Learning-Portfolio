#include "C_Code_0427Example.h"
void show_variable_address();
void pointer_exercise();
void pointer_exercise3();
void pointer_exercise2();
void variable_with_pointer(int*);
void pointer_exercise5();
void pointer_exercise_swap();
void add(int *);
void pointer_exercise_call_function();
void swap(int,int);
void swap_pointer(int *, int *);
void arithmetic_series(int, int *);
void pointer_exercise_arithmetic_series();
void pointer_exercise_rectangle();
void evaluate_rectangle_area_peri(int , int , int *, int *);
void pointer_function();
int *max(int *, int*);


int main(){
	
	//show_variable_address();
	//pointer_exercise();
	//pointer_exercise2();
	//pointer_exercise3();
	//pointer_exercise4();
	//pointer_exercise5();
	//pointer_exercise_assignment();
	//pointer_exercise_call_function();	
	//pointer_exercise_swap();	
	//pointer_exercise_arithmetic_series();
	//pointer_exercise_rectangle();
	pointer_function();

}
void show_variable_address(){	
	int a=5, b=10;
	double c=6.28;
	printf("a=%4d, sizeof(a)=%d, address: %04X\n", a, sizeof(a), &a);
	printf("b=%4d, sizeof(b)=%d, address: %04X\n", b, sizeof(b), &b);
	printf("c=%4.2f, sizeof(c)=%d, address: %04X\n", c, sizeof(c), &c);		
}
void pointer_exercise(){
	/*&ptr 是pointer的pointer*/
	/* 'ptr' 指向num的位址 -> &num */
	int *ptr;
	int num=20;
	ptr=&num;
	printf("*ptr=%d, ptr=%p, &ptr=%p, &num=%p \n",*ptr, ptr, &ptr, &num); 	
}
void pointer_exercise2(){	
	/* ptr 可以被重新指向*/	
	int a=8, b=9;
	int *ptr;
	ptr =&a;
	printf("&a=%p, ptr=%p, &ptr=%p,*ptr=%d \n",&a, ptr, &ptr, *ptr); 	
	ptr =&b;
	printf("&b=%p, ptr=%p, &ptr=%p,*ptr=%d \n",&b, ptr, &ptr, *ptr); 	
}
void pointer_exercise3(){
	/* "ptr" 跟 "*ptr" 的大小是不一樣的 */
	/* 整數型態 */
	int *ptri;
	char *ptrc;
	printf("sizeof(ptri)=%d\n", sizeof(ptri)); //8
	printf("sizeof(ptrc)=%d\n", sizeof(ptrc)); //8
	printf("sizeof(*ptri)=%d\n", sizeof(*ptri)); //4
	printf("sizeof(*ptrc)=%d\n", sizeof(*ptrc)); //1
}

void pointer_exercise4(){
	/*指標可以指向任意的變數，但是不會檢查型態*/
	int i_var =100, *ptri;
	float f_var =3.2f, *ptrf;
	ptri=&f_var;
	ptrf=&i_var;
	printf("sizeof(i_var)=%d\n", sizeof(i_var)); //4
	printf("sizeof(f_var)=%d\n", sizeof(f_var)); //8
	printf("i_var=%d, *ptri=%d\n",i_var,*ptri); //不會報錯，但是顯示會是非預期的數值 
	printf("f_var=%.lf, *ptrf=%.lf\n",f_var, *ptrf);//不會報錯，但是顯示會是非預期的數值	
	printf("===修正後===\n");
	ptri=&i_var;
	ptrf=&f_var;
	printf("i_var=%d, *ptri=%d\n",i_var,*ptri); 
	printf("f_var=%lf, *ptrf=%lf\n",f_var, *ptrf);	
}

void pointer_exercise5(){
		int var=886;
		int *ptri=&var;
		variable_with_pointer(ptri);		
}

void variable_with_pointer(int *ptr){
	printf("Variable content = %d \n",*ptr);	
}
void pointer_exercise_assignment(){
	int a =5, b=10;
	int *ptr1, *ptr2;
	ptr1=&a;
	ptr2=&b;
	printf("a=%p, b=%p, ptr1=%p, ptr2=%p\n", &a, &b, ptr1,ptr2);
	*ptr1=7;
	*ptr2=32;
	a=17; 
	ptr1=ptr2;/*記憶體指向同一個地方 (b)*/
	printf("a=%2d, b=%2d, *ptr1=%2d, *ptr2=%d\n", a, b, *ptr1, *ptr2); //17, 32, 32, 32
	*ptr1=9; /*記憶體指向同一個地方，所以*ptr1, *ptr2 都會改變 */
	printf("a=%2d, b=%2d, *ptr1=%2d, *ptr2=%d\n", a, b, *ptr1, *ptr2); //17, 9, 9, 9
	ptr1=&a; /*斷開 ptr1 指向a*/
	printf("a=%2d, b=%2d, *ptr1=%2d, *ptr2=%d\n", a, b, *ptr1, *ptr2); //17 ,9, 17, 9
	a=64;
	printf("a=%2d, b=%2d, *ptr1=%2d, *ptr2=%d\n", a, b, *ptr1, *ptr2); //64, 9, 64, 9
	*ptr2=*ptr1+5; /* 'ptr2' 一直都是指向b*/
	printf("a=%2d, b=%2d, *ptr1=%2d, *ptr2=%d\n", a, b, *ptr1, *ptr2); //64, 69, 64, 69
	printf("a=%p, b=%p, ptr1=%p, ptr2=%p\n", &a, &b, ptr1,ptr2); //a, b, a, b																  
	
}

void pointer_exercise_call_function(){	
	int a=20;
	int *ptr =&a;
	printf("Before call add() function, a=%d\n",a);
	add(ptr);
	printf("After call add() function, a=%d\n",a);	
}

void add(int *ptr){	
	*ptr +=30;	
}

void pointer_exercise_swap(){
	
	int a=17, b=25;
	printf("Before swap... \n");
	printf("a=%d, b=%d\n",a,b);
	swap(a,b);
	printf("After swap... \n");
	printf("a=%d, b=%d\n",a,b);
	swap_pointer(&a,&b);
	printf("After swap with pointer... \n");
	printf("a=%d, b=%d\n",a,b);
}
void swap(int a, int b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
}
void swap_pointer(int *a, int *b){	
	int tmp =*a;
	*a=*b;
	*b=tmp;	
}
void pointer_exercise_arithmetic_series(){	
	int index, total;
	printf("Please input a integer :\n");
	scanf("%d", &index);	
	fflush(stdin);
	arithmetic_series(index, &total);
	printf("The result is : %d\n", total);	
}
void arithmetic_series(int index, int *total){
	int i=1;
	int result=0;
	for(i=1; i<= index; i++){		
		result +=i;		
	}
	*total=result;	
}
void evaluate_rectangle_area_peri(int width, int length , int *area, int *peri){	
	*area = width* length;
	*peri =2*width + 2*length;	
}
void pointer_exercise_rectangle(){
	int a=5, b=8;
	int area, peri;	
	evaluate_rectangle_area_peri(a,b,&area,&peri);	
	printf("area =%d, total length=%d\n", area, peri);		
}
void pointer_function(){	
	int a=56, b=78, *ptr;
	ptr=max(&a, &b);
	printf("max=%d \n", *ptr);
}
int *max(int *a, int*b){
	/*方法回傳指標*/	
	if (*a>*b) return a;
	else return b;	
}



