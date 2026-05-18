#include <stdio.h>
#include <string.h>
#define USERNAME_LEN 20
#define PASSWD_LEN 8
int main(void)
{
    char name[USERNAME_LEN+1];
    char passwd[PASSWD_LEN+1];


    printf("Hi, input your user name?\n");
    fgets(name, USERNAME_LEN+1, stdin);
    name[strlen(name)-1]='\0';
     printf("Hi, input your password?\n");
    fgets(passwd, PASSWD_LEN+1, stdin); 
    passwd[strlen(passwd)-1]='\0';
    printf("%s : %s\n",name, passwd);
    getchar();
    return 0;
}
