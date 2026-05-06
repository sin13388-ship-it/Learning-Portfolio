#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
 	
 	short value_1, value_2, result;
 	int length;
 	
 	length =sizeof(short);
 	printf("The size of \"short\" is %d \n", length);
 	length =sizeof(int);
 	printf("The size of \"int\" is %d \n", length); 	
 	
 	
 	value_1=-1;
 	printf("Value 1 =%#X\n", value_1);
 	value_1=-100;
 	printf("Value 1 =%#X\n", value_1);
	
	value_1=-112;
 	printf("Value 1 =%#X\n", value_1);
 	
 	value_1=32765;
 	value_2=10;
 	value_1+=value_2;
 	printf("Value 1 + Value 2 =%d\n", value_1); //overflow
 	
 	value_1=-32765;
 	value_2=-10;
 	value_1+=value_2;
 	printf("Value 1 + Value 2 =%d\n", value_1); //overflow
 	
 	
 	
	getchar();
	return 0;
}
