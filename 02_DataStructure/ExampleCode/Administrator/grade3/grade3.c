#include "grade.h"
#include <stdio.h>

int main()
{
 //char name[30] ;
 //int ID ;
 //int grade[3] ;
 GRADE grade ;
 
 int student_no ;
 int i , j;

 FILE * fp ;

 fp = fopen("grade.txt","w") ;
 if(fp == NULL)
 {
	printf("file open error!") ;
	return 0 ;
 }

 printf("please input student number:") ;	
 scanf("%d",&student_no) ;

 for(i=0;i<student_no;i++)
 {
	printf("please input NO %d student info.\n",i+1) ;
	printf("name:") ;
	scanf("%s",grade.name) ;

	printf("ID:") ;
	scanf("%d",&(grade.ID)) ;

	for(j=0;j<3;j++)
	{
		printf("Grade %d:",j+1) ;
		scanf("%d", &(grade.grade[j]) ) ;
	}

	// write to file - grade.txt
	fprintf(fp,"%10s %2d %3d %3d %3d\n",
		grade.name,grade.ID,grade.grade[0],grade.grade[1],grade.grade[2]) ;

	printf("\n") ;
 }

 fclose(fp) ;
}
