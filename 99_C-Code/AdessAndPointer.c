#include "C_Code_0427Example.h"
void show_variable_address();
void pointer_exercise();
void pointer_exercise3();
void pointer_exercise2();
void variable_with_pointer(int*);
void pointer_exercise5();

int main(){
	
	//show_variable_address();
	//pointer_exercise();
	//pointer_exercise2();
	//pointer_exercise3();
	//pointer_exercise4();
	pointer_exercise5();
	

	
		

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







