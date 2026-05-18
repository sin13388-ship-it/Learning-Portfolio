#include <stdio.h>
#define MAX 8
int main(void)
{
    char line[MAX];
   printf("[press ENTER to exit?]\n");
   while (fgets(line, MAX, stdin) && line[0]!='\n') {
      fputs(line, stdout);  
      printf("[press ENTER to exit?]\n");
   
    }
      
   system("pause");

  return 0;
}
