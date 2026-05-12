#include "C_Code_0512Example.h"

struct data{
	char name[10];
	int math;
};
typedef struct data student;

typedef struct scores{
	
	char name[10];
	int student_id;
	int chinese;
	int english;
	
} scores;

void exercise1_structure_pointer();
void exercise2_structure_get_result();
void exercise3_structure_array();
void exercise4_structure_swap();


void structure_pointer();
void add5(student *std);
void result(const scores *score);
void swap(student *std1, student *std2);
scores *maximum(const scores *arr, int count);


int main(){	
	//exercise1_structure_pointer();
	//exercise2_structure_get_result();	
	//exercise3_strucutre_array();
	//exercise4_structure_swap();
	//exercise5_typedefine();
	//exercise6_union();
	exercise7_payment_select();
	getchar();
	return 0;
}
void exercise1_structure_pointer(){	
	student std={"Jenny",75};
	printf("Before : Name= %s, math=%d\n", std.name, std.math);
	add5(&std);
	printf("After : Name= %s, math=%d\n", std.name, std.math);	
}
void add5(student *std){	
	std->math +=5;
}
/*
雖然「傳值」在邏輯上最安全（因為函數拿的是副本），
但在 C 語言中，為了追求效能，我們通常選擇 「傳址 + const」。
這能達到與傳值一樣的安全性，同時擁有極高的執行效率。
*/

void exercise2_structure_get_result(){	
	scores std1 ={"JJ Chen",2601,78,52};
	scores std2 ={"KK Lin",2602,75,81};
	result(&std1);
	result(&std2);
}
void exercise3_strucutre_array(){
	scores score[3]={{"Antony",2601,83,87},{"Candy",2602,85,50},{"Anne",2603,72,60}};
	scores *max=score;	
	max=maximum(score, 3);
	printf("Name: %s\n", score->name);
	printf("Student ID: %d\n",score->student_id);
	printf("English: %d\n",score->english);	
}
void exercise4_structure_swap(){
	
	student std1={"Freda",73};
	student std2={"Teresa",88};
	
	printf("Before swap \n");
	printf("std_01=%s, score=%d \n", std1.name, std1.math);
	printf("std_02=%s, score=%d \n", std2.name, std2.math);
	
	swap(&std1,&std2);
	printf("Before swap \n");
	printf("std_01=%s, score=%d \n", std1.name, std1.math);
	printf("std_02=%s, score=%d \n", std2.name, std2.math);
	
}



void result(const scores *score){
	printf("Name: %s\n", score->name);
	printf("Student ID: %d\n",score->student_id);
	if((score->chinese+score->english)>175){
		printf("Great!\n");
	}
	else if((score->chinese+score->english)>155){
		printf("Good\n"); 
	}
	else
	{
		printf("It requires hard work\n");
	}
}
scores *maximum(const scores *arr, int count){	
	const scores *ptr;
	ptr=arr;
	const scores *max_ptr;
	max_ptr=ptr;
	int i=0;
	
	for(i=1;i<count;i++){		
		if ((ptr+i)->english > max_ptr->english){
			max_ptr=(ptr+i);
		}
	}
	return max_ptr;	
}
void swap(student *std1, student *std2){	
	student tmp;	
	tmp=*std1;
	*std1=*std2;
	*std2=tmp;
}


