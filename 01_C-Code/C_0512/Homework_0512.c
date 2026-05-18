#include "C_Code_0512Example.h"

enum machine{
	running=1,
	mantainance,
	failed
}state;

enum color{
	red,
	green,
	blue
};

enum card{
	Platinum,
	Gold,
	Silver
} mycard;

union size_u{
	int math;
	float sum;
	char id;
}myUnion;
struct size_s{
	int math;
	float sum;
	char id;
}struct1;

void homework1();
void homework2();
void homework3();
void homework4();

void homework1(){
	
	printf("Homework01=====\n");
	
	int state;
	
	printf("輸入機器生產狀態 [1: running\ 2: mantainance\ 3: failed]: \n");
	scanf("%d",&state);
	fflush(stdin);
	
	switch (state){
		case running:
			printf("機器正常運轉中\n");
			break;
		case mantainance:
			printf("機器目前維修中\n");
			break;
		case failed:
			printf("機器目前故障中\n");
			break;
		
	}
}


void homework2(){
	printf("Homework02=====\n");
	char color_text[3][6]={"Red","Green","Blue"};
	
	printf("輸入顏色，不區分大小寫 [R/G/B]: \n");
	
	char color_code;
	
	scanf(" %c",&color_code);
	fflush(stdin);
	
	switch (color_code){
		case 'r':
		case 'R':
			printf("The color is %s\n", color_text[red]);
			break;
		case 'g':
		case 'G':
			printf("The color is %s\n", color_text[green]);
			break;
		case 'b':
		case 'B':
			printf("The color is %s\n", color_text[blue]);
			break;
		default :
			printf("Invalid input \n");
	}	
	
}

void homework3(){
	printf("Homework03=====\n");
	
	printf("Please input your card level : [0:Platinum 1:Gold 2: Silver]\n");
	
	scanf("%d",&mycard);
	fflush(stdin);
	int amount;
	
	
	printf("Please input your amount\n");
	scanf("%d",&amount);
	fflush(stdin);
	
	switch(mycard){
		case Platinum: 
			printf("打折完為 %d\n", (int) (amount * 0.8 ));
		break;
		case Gold: 
			printf("打折完為 %d\n", (int) (amount * 0.85 ));
		break;
		case Silver: 
			printf("打折完為 %d\n", (int) (amount * 0.9 ));
		break;
		default :
			printf("打折完為 %d\n", (int) (amount * 1 ));
	}
	
}
void homework4(){
	printf("Homework04=====\n");
	printf("The sizeof myunion %d \n", sizeof(myUnion));
	printf("The sizeof struct1 %d \n", sizeof(struct1));	
	
}


