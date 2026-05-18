
#include <stdio.h>
#include <string.h>

int main(void)
{
	char orig[] = "I love C Language";
	char string[strlen(orig)+1];
	printf("%d\n",sizeof(string));
	strcpy(string,orig);
	char *token = strtok(string, " ");
	while(token != NULL)
	{
		printf("[%s]\n", token);
		token = strtok(NULL, " ");
	}
	puts(orig);

	return 0;
}

