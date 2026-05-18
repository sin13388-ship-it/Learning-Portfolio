#include <stdio.h>
#define MAX 8
#define PASSWD "secret"
int check_passwd(char *user,char *secret);
int main(void)
{
    char line[MAX];
    int r;
    printf("Please input passwd(\"secret\")\n");
   
   while (fgets(line, MAX, stdin)) {

      r=check_passwd(line,PASSWD);
      printf("%d\n",r);
       printf("Please input passwd(\"secret\")\n");
     
    }
      
   system("pause");

  return 0;
}

int check_passwd(char *user,char *secret)
{
   int i=0;
   
   while (secret[i]!='\0' && secret[i]==user[i])
                  i++ ;
                   
   if (i!=6) return -1;
    else return 0;
   
    
}
