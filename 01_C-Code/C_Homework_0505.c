#include "C_Code_0505Example.h"

void homework_1();
void homework_2();
void homework_3();
void homework_4();

void homework_1(){
	
	struct computer_info{
		char vendor[10];
		int ram_size;
		char os_name[20];
		int disc_size;
	};
	struct computer_info comp;
	
	printf("Homework01======\n");
	
	printf("Please input your CPU brand:\n");
	fgets(comp.vendor,10,stdin);
	comp.vendor[strcspn(comp.vendor,"\n")]=0;
	fflush(stdin);
	
	printf("Please input your RAM size (GB):\n");
	scanf("%d", &comp.ram_size);
	fflush(stdin);
	printf("Please input your OS name:\n");
	fgets(comp.os_name,20,stdin);	
	comp.os_name[strcspn(comp.os_name,"\n")]=0;
	fflush(stdin);
	printf("Please input your disc size (GB):\n");
	scanf("%d", &comp.disc_size);
	fflush(stdin);
	
	printf("CPU : %s \n", comp.vendor);
	printf("RAM : %d GB\n", comp.ram_size);
	printf("OS : %s\n", comp.os_name);
	printf("Disc size : %d GB\n", comp.disc_size);	
	
}

void homework_2(){
	struct data{
		char name[15];
		int chinese;
		int physics;
	}student[2]={{"Vera",90,80},{"Bill", 85,70}};
	
	printf("Homework02======\n");	
	struct data *ptr;
	ptr = student;
	int sum=0;
	int i;	
	for(i=0; i<2; i++){		
		printf("Name= %s , chinese =%d, physics = %d\n", (ptr+i)->name,(ptr+i)->chinese, (ptr+i)->physics );
		sum +=(ptr+i)->physics;
	}	
	printf("physics sum = %d\n",sum );
}

void homework_3(){
	printf("Homework03======\n");
	int IOT[2][5]={{11,22,33,44,55},{2,4,7,8,9}};
	int *target;
	int i, j;
	for(i=0; i<2; i++){
		for(j=0; j<5; j++){
			printf("%d \t", *(*(IOT+i)+j));
			if (*(*(IOT+i)+j)==7) target=*(IOT+i)+j;
		}
		printf("\n");
	}	
	*target +=6;
	for(i=0; i<2; i++){
		for(j=0; j<5; j++){
			printf("%d \t", *(*(IOT+i)+j));		
		}
		printf("\n");
	}
}
void homework_4(){
	struct area{
		char position[30];
		int post_code;
	};
	struct Person{
		char city[30];
		struct area addr;
	};	
	struct Person tom={"Taoyuan",{"Yangmei", 326023}};
	printf("Homework04======\n");
	printf("City : %s\n", tom.city);
	printf("Area : %s\n", tom.addr.position);
	printf("post_code : %d\n", tom.addr.post_code);
	
}

