#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME_LEN 20
#define PASSWD_LEN 8

char name[USERNAME_LEN|+1];


void display_menu(void);
void user_menu();
void eat_char();
int get_password(char *passwd);
int set_password(char *passwd);	 
int authenticate(char *passwd,char *user_password);

int main(void)
{
     char passwd[PASSWD_LEN+1]="abc";
     char command;
       display_menu();

  while (1) {
    printf("enter key to choose your function:");
      command=getchar();
       
	switch (command)
	{
		case 'a':
		
			printf("a)aaa\n");
			break;
		case 'b':
		   set_password(passwd);
			break;
		case 'c':
		   get_password(passwd);
			break;
		
		case 'h':
             display_menu();
			break;
				
		case 'q':
            exit(0);
			break;	
			
		default:
	    printf("Invalid Operation, press 'h' for help\n");
			break;
	}
	   while(getchar()!='\n');
  }
    
 
  return 0;
  
}

int get_password(char *passwd)
{
    printf("password is : %s\n",passwd);  
    return 0;
}

int set_password(char *passwd)
{
   char tmp_passwd[PASSWD_LEN+1];
   int r;
  eat_char();
  
   printf("input your original passworld:");
    fgets(tmp_passwd, PASSWD_LEN+1, stdin); 
    tmp_passwd[strlen(tmp_passwd)-1]='\0';
    r=authenticate(passwd,tmp_passwd);
    
    if (r==0){
      printf("your input password is incorrect, exit\n");            
      return -1;
      
      } 
    printf("input your NEW passworld (max:8 character):");
    fgets(tmp_passwd, PASSWD_LEN+1, stdin); 
    tmp_passwd[strlen(tmp_passwd)-1]='\0'; 
    strcpy(passwd,tmp_passwd);
    printf("new passwd saved,press any key to return to menu\n");
    
   return 0;
}

int authenticate(char *passwd,char *user_password)
{
    
  if (!strcmp(passwd,user_password) /*&& !strcmp(name,user_name)*/) 
     return 1;  // legal user
 else
     return 0;


}


void eat_char() {
  while(getchar()!='\n');
}
void display_menu(void)
{
  printf("a) aaaaaaaa\n");
  printf("b) Set Password\n");
  printf("c) Query Password\n");
  printf("q) Quit\n");
  printf("h) display menu\n");
  
  
}


