#include <stdio.h>
#include <string.h>
void sort(int *s,int n);
void show_all(int *s, int size);
void sort_str(char **s,int n);
void show_str(char (*s)[20], int size);

int main(void)
{
    
    int a[4]={1,22,3,4};
    sort(a,4);
    show_all(a,4);
    
#if 1
        char company[5][20]={         
         "apple",
         "samsung",
         "htc",
         "blackberry",
         "sony",
          
         };
          
      show_str(company,5);
      //sort_str(company,5);
#endif    
    
    
    
 getchar();
 return 0;

}
#if 1
void sort_str(char **s,int n)
{
     int i,j;
     char *temp;
     char *ptr[5];
       
for (i=1; i <= n; i++) 
 { 
	for (j = n; j > i; j--) 
	{ 
		if (strcmp(s[j-1],s[j])) 
		{ 
			temp = s[j-1]; 
			s[j-1] = s[j]; 
			s[j] = temp; 
		} 
	} 
 }
 
} 
#endif

void sort(int *s,int n)
{
     int i,j,temp;
for (i=1; i <= n; i++) 
 { 
	for (j = n; j > i; j--) 
	{ 
		if (s[j-1] > s[j]) 
		{ 
			temp = s[j-1]; 
			s[j-1] = s[j]; 
			s[j] = temp; 
		} 
	} 
 }
 
} 


void show_str(char (*s)[20], int size)
{
    int r;

    for (r = 0; r < size; r++)
    {
         printf("%s \n",s[r]);       
    }
    
}

void show_all(int *s, int size)
{
    int r;

    for (r = 0; r < size; r++)
    {
         printf("%d ",s[r]);       
    }
     printf("\n");
}


