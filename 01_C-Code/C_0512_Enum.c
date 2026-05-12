#include "C_Code_0512Example.h"

void exercise8_enum();
void exercise9_Iterate();
void exercise11_select_trousers();

enum fruit{
	//未給定初值，從0開始自動加 1 
	APPLE,
	ORANGE,
	GRAPE
};
enum rgbColor{
	//有給定初值，會從指定的數字開始遞增	
	RED=10,
	GREEN,
	BLUE	
};
enum animal{
	//每個都有給，可以不連續的值 
	LION=1,
	TIGER=11,
	BEAR=21
};
enum week
{
	sun, mon, tue, wed, thu, fri, sat
}day; //宣告一個變數day 

enum color{
	red=114,
	green=103,
	blue=98
};

void exercise8_enum(){	
	printf("APPLE=%d\t ORANGE=%d\t GRAPE=%d\n",APPLE,ORANGE,GRAPE);
	printf("RED=%d\t GREEN=%d\t BLUE=%d\n",RED,GREEN,BLUE); 
	printf("LION=%d\t TIGER=%d\t BEAR=%d\n",LION,TIGER,BEAR);
}
void exercise9_Iterate(){	
	//列舉可以和for loop 一起使用	
	for(day=sun; day<=sat;day++) printf("Enumeration element : %d\n", day); 
}
void exercise10_salary(){
	//與switch case 連用 
	int total=0, pay ,hour; 
	char days[7][4]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	for(day=sun;day<=sat;day++){
		
		printf("Please enter your working hours from Sunday to Saturday: %s \n", days[day]);
		scanf("%d", &hour);
		fflush(stdin);
		switch(day){
			case sun:
				pay=hour *260;
				break;
			case sat:
				pay=hour *230;
				break;
			default:
				pay=hour *196;
				break;
		}
		total +=pay;
	}
	printf("Total salary = %d\n", total);
	
}

void exercise11_select_trousers(){
	
	enum color trousers;
	char key;
	do{
		printf("Please input the color {r,g,b} \n");
		scanf("%d",&key);
		fflush(stdin);	
		
	}while(key!=red && key!=green && key!=blue);
	
	trousers=key;
	
	switch (trousers){
		case red:
			printf("You selected Red\n");
			break;
		case green:
			printf("You selected Green\n");
			break;
		case blue:
			printf("You selected Blue\n");
			break;
	}
	
}








