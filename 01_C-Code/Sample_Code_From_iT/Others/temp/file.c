#include <stdio.h>
#include <stdlib.h>

int main(void)
{

FILE *ptr;
//char name[10];
char name[30];
int ID;
short grade[3];
int i,j,max=3;

if((ptr=fopen("test.txt","w"))==NULL)
{
	printf("Can not open file!");
}
printf("You can insert three guys info.");

for(i=0;i<max;i++)
{
	printf("Insert Name :");
	scanf("%s", name);
	printf("Insert ID :");
	scanf("%d", &ID);
	printf("IDx = %d\n",ID) ;
	
	 for(j=0;j<3;j++)
	  {
	  	printf("Insert grade :");
	    scanf("%sd", &(grade[j]));
	  }
	
	printf("ID = %d\n",ID) ;
	fprintf(ptr, "%10s,%5d, %3d, %3d, %3d\n", name,ID,grade[0],grade[1],grade[2]);
}


//ptr = fopen("C:\\cygwin\\home\\user\\file\\test.txt","w");
//fwrite(name, sizeof(char), 10, ptr);

//printf("Please insert ST_ID : ");
//scanf("%c",ID);
//printf("Please insert ST_Grade : ");
//scanf("%c",grade[i]);
//ptr = fopen("C:\\cygwin\\home\\user\\file\\test.txt","wt");
//fprintf(ptr,"%s", name[i]);


//ptr = fopen("C:\\cygwin\\home\\user\\file\\test.txt","wt");
//ptr = fopen("C:\\cygwin\\home\\user\\file\\test.txt","wt");
//fprintf(ptr,"%s", name);

fclose(ptr);
return 0;
}