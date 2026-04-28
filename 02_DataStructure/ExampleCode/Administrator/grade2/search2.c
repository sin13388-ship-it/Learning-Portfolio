#include <stdio.h>
#include <string.h>

#define SEARCH_NAME "john"


int main()
{
 char name[30] ;
 int ID ;
 int grade[3] ;

 FILE * fp ;
 int result ;
 
 // +4 : spacex4,  +1 : \n
 int record_size = 10+2+3+3+3 +4 + 1 ;
 int record_no ; 
 int total_record_no ;

 printf("which record you want to query?") ;
 scanf("%d",&record_no) ;

 fp = fopen("grade.txt","r") ; // text mode
 if(fp == NULL)
 {
	printf("file not exit\n") ;
	return 0 ;
 }

 // get total record number
 fseek(fp,0,SEEK_END) ; 
 result = ftell(fp) ;
 total_record_no  = result / record_size ;
 
 if(record_no > total_record_no)
 {
	printf("total record = %d, and your input is out of range!\n",
		total_record_no) ;
	return 0 ;
 }


 // move file pointer
 fseek(fp,(record_no-1)*record_size,SEEK_SET) ;

 result = fscanf(fp,"%s %d %d %d %d",
		name,&ID,&(grade[0]),&(grade[1]),&(grade[2])) ; 

 printf(" name = %s\n ID=%d\n grade1=%d\n grade2=%d\n grade3=%d\n",
	name,ID,grade[0],grade[1],grade[2]) ;
	
	
	/*
 // print out all data	
 fseek(fp,0,SEEK_SET) ;
 while(1)
 {
	 	result = fscanf(fp,"%s %d %d %d %d",
			name,&ID,&(grade[0]),&(grade[1]),&(grade[2])) ;
		if(result != 5)
			break ;
	 	else
	 	{
			 printf(" name = %s\n ID=%d\n grade1=%d\n grade2=%d\n grade3=%d\n\n",
				name,ID,grade[0],grade[1],grade[2]) ;
	 	}
 } 
*/

 fclose(fp) ;

}
