#include "C_Code_0505Example.h"
void structure_exercise();
void structure_size();
void structure_initialize();
void define_struct_also_create(); 
void struct_assignment();
void struct_array_and_its_size();
void nested_structure();
void structure_assignment_using_stdin();
void time_elapse();
void nested_struct_now();
void student_data();
void structure_pointer();
void structure_pointer_get_value();
struct data{
	char name[20];
	int math;
};

struct staff_information{
	char name[18];
	int seniority;
};

void structure_exercise(){	
	struct data student1;
	printf("Please type in your name: \n");
	fgets(student1.name,20,stdin);
	student1.name[strcspn(student1.name,"\n")]=0;
	printf("Please input your score: \n");
	scanf("%d", &student1.math); //int 不是參考型別，所以要用&取得pointer 
	fflush(stdin);
	printf("Name = %s \n", student1.name);
	printf("Score = %d \n", student1.math);	
}

void structure_size(){
	/*strcture 會進行記憶體補齊，假設結構中的欄位byte數不同，
	會以大的型態大小補齊 	
	18 +4 =22 >> 對齊4 bytes >> 22+2 =24 bytes 
	如果是short 而不是 int , 18 +2 =20
	但也會因為編譯器的不同而可能是22 
	*/ 	
	struct staff_information teacher;	
	printf("sizeof(teacher)=%d\n", sizeof(teacher));
}
void structure_initialize(){
	struct data student2={"Vera", 95};
	printf("Name = %s \n", student2.name);
	printf("Score = %d \n", student2.math);
}

void define_struct_also_create(){
	struct student_info{
		char name[15];
		int sex;
		int age;
	}student1={"Vera chang",0,18}, student2={"Jhon Wang", 1, 19};
	
	printf("%s Gender: ", student1.name);
	if(student1.sex==1) printf("Male");
	else printf("Female");
	printf("\nage: %2d\n", student1.age);
	
	printf("%s Gender: ", student2.name);
	if(student2.sex==1) printf("Male");
	else printf("Female");
	printf("\nage: %2d\n ", student2.age);
}
void struct_assignment(){
	//結構必須型態相同才能assignment 
	struct data_int{
		char name[15];
		int math;
	}s1={"Lily chen",83};
	
	struct data_float{
		char name[15];
		float math;
	};
	/*	
	struct data_float s2;
	s2=s1; //會出錯 
	*/	
	struct data_int s2;
	s2=s1;
	printf("s1.name=%s, s1.math=%d\n", s1.name, s1.math);
	printf("s2.name=%s, s2.math=%d\n", s2.name, s2.math);

	strcpy(s1.name, "Vera"); //structure 是指向陣列的pointer 不能直接賦值。要透過strcpy copy 過去 
	printf("s1.name=%s, s1.math=%d\n", s1.name, s1.math);
	printf("s2.name=%s, s2.math=%d\n", s2.name, s2.math);	
	
}
void struct_array_and_its_size(){
	//23+4 =27 >> 對齊 28 >> 28 * 18 =504 
	struct data_int{
		char name[23];
		int score;
	}student[18];
	
	printf("sizeof(student)=%d\n", sizeof(student));	
}

void nested_structure(){
	
	struct date{
		int year;
		int month;
		int day;
	};
	
	struct student_info{
		char name[20];
		int score;
		struct date birthday;		
	}student={"Mary Wang", 95, {93,10,2}}; //Nested 結構一樣用{}初始化 
	printf("%s, Birthday: %d/%d/%d\n", student.name, student.birthday.year,student.birthday.month,student.birthday.day); 	
	//非初始化的都要個別賦值	
	student.birthday.year =80;
	student.birthday.month=5;
	student.birthday.day=23;	
	printf("%s, Birthday: %d/%d/%d\n", student.name, student.birthday.year,student.birthday.month,student.birthday.day); 
	printf("Score = %d \n", student.score);		
}

void structure_assignment_using_stdin(){
	struct date{
		int year;
		int month;
		int day;
	}holiday={2026,6,13}, festival;
	
	do {
		printf("Please input 2026: \n");
		scanf("%d", &festival.year);
		fflush(stdin);
	}while(festival.year !=2026);
	do {
		printf("Please input 6: \n");
		scanf("%d", &festival.month);
		fflush(stdin);
	}while(festival.month !=6);
	do {
		printf("Please input 13: \n");
		scanf("%d", &festival.day);
		fflush(stdin);
	}while(festival.day !=13);
	printf("\nholiday=%02d/%02d/%02d\n", holiday.month, holiday.day, holiday.year);
	printf("festival=%02d/%02d/%02d\n", festival.month,festival.day, festival.year);
	printf("sizeof(festival)=%d\n", sizeof(festival));	
}
void time_elapse(){
	
	struct time{
		int hour;
		int minute;		
	}start={12,32}, end={15,13}, elapse={0,0};
	
	printf("start= %2d:%2d\n",start.hour, start.minute);
	printf("end= %2d:%2d\n",end.hour, end.minute);
	elapse.minute =end.minute-start.minute;
	if(elapse.minute <0) {
		elapse.minute +=60; //borrow
		end.hour--;
	}
	elapse.hour=end.hour-start.hour;
	printf("elapse= %2d:%2d\n",elapse.hour, elapse.minute);	
}

void nested_struct_now(){
	struct time{
		int hour;
		int minute;		
	};
	struct date{
		int year;
		int month;
		int day;
		struct time crt;
	}now={2026,5,5,{14,12}};	
	printf("Now=> %02d/%02d/%02d %02d:%02d\n",now.month,now.day, now.year,now.crt.hour, now.crt.minute);
}
void student_data(){
	
	/*structur array*/
	
	struct student_info{
		char name[15];
		int age;
		int score;		
	}student[3];	
	int i;
	for(i=0; i<3; i++){
		printf("Pleast input student%d.name :\n",i+1);
		fgets(student[i].name,15,stdin);
		student[i].name[strcspn(student[i].name,"\n")]=0;
		fflush(stdin);
		printf("Pleast input student%d.age :\n",i+1);
		scanf("%d", &student[i].age);
		fflush(stdin);
		printf("Pleast input student%d.score :\n",i+1);
		scanf("%d", &student[i].score);
		fflush(stdin);
	}	
	for(i=0; i<3; i++){
		printf("%s \nAge: %d Score: %d\n",student[i].name, student[i].age,student[i].score);
	}
}
void structure_pointer(){
	
	struct student_data{
		char name[15];
		int math;
		int eng;
		int chi;
	}student;
	struct student_data *ptr; //宣告成指向一個結構的指標 
	ptr = &student; // 一樣要給位置 
	
	printf("Pleast input student.name :\n");
	fgets(ptr->name,15,stdin);
	ptr->name[strcspn(ptr->name,"\n")]=0;
	fflush(stdin);
	printf("Pleast input math :\n");
	scanf("%d", &ptr->math);
	fflush(stdin);
	printf("Pleast input eng : \n");
	scanf("%d", &ptr->eng);
	fflush(stdin);
	printf("Pleast input chi : \n");
	scanf("%d", &ptr->chi);
	fflush(stdin);
		
	printf("%s \nMath: %d Eng: %d  Chi: %d\n",ptr->name, ptr->math, ptr->eng, ptr->chi); //ptr->math = (ptr.math)用指標的方式 	
	printf("Average = %1f", (float)(ptr->math + ptr->eng +  ptr->chi )/3); //整數除法要型轉 

}

void structure_pointer_get_value(){
	struct employee{
		char name[20];
		int salary;
		char department[20];
	}manager={"William", 60000, "System team"};
	
	struct employee *ptr;
	ptr=&manager;
	printf("Name: %s\n", ptr->name);
	printf("Salary: %d\n", ptr->salary);
	printf("department: %s\n", ptr->department);
	
	
}
