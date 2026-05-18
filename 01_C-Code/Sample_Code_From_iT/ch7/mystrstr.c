
#include <stdio.h>
#include <string.h>
char * my_strstr(char *s,char *key);
int main(void)
{
  char str[] = "I love C Language";
  char *key="kk";
  char *ret;
  ret=my_strstr(str,key);
  if (ret)
	  printf("\"%s\" is found in \'%s\'\n",key,str);
  else 
	  printf("\"%s\" is NOT found in \'%s\'\n",key,str);

  return 0;
}

char * my_strstr(char *s,char *key)
 {

    int i;
	int slen=strlen(s);
	int klen=strlen(key);
    char *t=NULL; 
	for(i=0;i<slen;i++) {
		if (!strncmp(s+i,key,klen)) {
             t=s+i;               
			 break;
		}
    }
    
	return t;
}

