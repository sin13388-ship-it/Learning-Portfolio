#include <stdio.h>
#include <string.h>

main()
{
  char * word;
  char string []="abc def ghi jkl mno pq rstu v wxy z";
  int counter = 1;

  printf("ORG string = %s \n",string) ;

  word=strtok(string, " ") ;
  while( word != NULL)
  {
  	printf("Token %d = %s \n",counter++,word) ;
   	word=strtok(NULL, " ");
  }  
  
  printf("ORG string = %s \n",string) ;
}




