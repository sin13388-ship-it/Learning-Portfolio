#include <stdio.h>
#include <stdlib.h>

//struct student
//{
//  char name[30];
//  int ID;
//  short grade[3];
//};

//struct student data;
//scanf("%s %d %d %d %d", data.name, data.ID, data.grade[0], data.grade[1], data.grade[1]);
//fwrite(&data, sizeof(struct data), 1, fp);
//fseek(fp, n*sizeof(struct data, SEEK_SET);
//fread(&data, sizeof(struct data), 1, fp);


int main(void)
{
char name[30];
int id;
short grade[3];
  FILE* fp;

  fp = fopen("grade.txt","w");

  while (1)
  {
    printf("Input Name:   ");
    gets(name);
    if (strcmp(name,"") == 0)
    	break;
 
    printf("Input ID:     ");
    scanf("%d",&id);
    printf("Input Grade1: ");
    scanf("%hd",&(grade[0]));
    printf("Input Grade2: ");
    scanf("%hd",&(grade[1]));
    printf("Input Grade3: ");
    scanf("%hd",&(grade[2]));

printf("%d %d %d\n",grade[0],grade[1],grade[2]) ;

    fprintf(fp,"%s %4d %4d %4d %4d\n\n\n", name, id, grade[0], grade[1], grade[2]);
    printf("\n");
    gets(name);
  }

  fclose(fp);
  return 0;

}


