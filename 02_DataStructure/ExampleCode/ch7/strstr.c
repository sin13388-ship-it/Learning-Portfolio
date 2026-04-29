#include <stdio.h>
#include <string.h>  /* declares the strcat() function */
#define SIZE 80
int main(void)
{
   char *p;
   char email[] = "robot@ittraining.com.tw";
   puts(email);
   p=strchr(email,'@');   
   printf("@ is located at %dth word\n",p-email+1);
   p=strstr(email,"training");
   if (p!=NULL) 
      puts(p);
   getchar();
   return 0;
}
