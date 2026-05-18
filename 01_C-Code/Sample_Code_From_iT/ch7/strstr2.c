#include <stdio.h>
#include <string.h>

int main(void)
{
   char *p;
   int count=0;
   char *str="hello apcs I love apcs from now on" ;
   puts(str);
   p=str;
   while ((p=strstr(p,"apcs"))!=NULL) {
     count++;
     p++;
   }
   printf("\"apcs\" occurs %d times\n",count);

   return 0;
}
