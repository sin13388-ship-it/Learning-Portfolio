#include <stdio.h>
#define MAX 20


int main(void)
{
    char name[MAX];
    char * ptr;
    printf("Hi, what's your name?\n");
  
        
    ptr = fgets(name, MAX, stdin);
    printf("%s\n", name);
    printf("%s\n", ptr);
    getchar();
    return 0;
}
