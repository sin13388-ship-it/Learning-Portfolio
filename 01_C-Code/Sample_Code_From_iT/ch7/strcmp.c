#include <stdio.h>
#include <string.h>   /* declares strcmp() */
#define PASSWORD "1234"
#define MAX 40
int main(void)
{
    char try[MAX];
    printf("Please input your passwrod (default is %s)? ",PASSWORD);
    gets(try);
    while (strcmp(try,PASSWORD) != 0)
    {
        puts("No, that's wrong. Try again.");
        gets(try);
    }
    puts("That's right!");
    system("pause");
    return 0;
}
