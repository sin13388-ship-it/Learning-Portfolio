
#include <stdio.h>
#include <string.h>

int main(void)
{
	char string[] = "I love C Language";
	char *token = strtok(string, " ");
	while(token != NULL)
	{
		printf("[%s]\n", token);
		token = strtok(NULL, " ");
	}
	getchar();
	return 0;
}

