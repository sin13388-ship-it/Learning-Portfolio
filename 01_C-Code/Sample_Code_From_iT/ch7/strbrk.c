#include <stdio.h>

char *func(const char *s1,const char *s2);
int main(void)
{
    char *c;
    char name[]="he495uilaaz3";
    c=func(name,"0g123456789"); 
 
    if (c!=NULL) printf("find first character is %c\n",*c);
     else printf("not found !\n");
     
    system("pause");
    return 0;
}


char *func(const char *s1,const char *s2)
{
     int i;
     const char *p=NULL;
     const char *q;
 
     for(i=0;s2[i]!='\0';i++) {
        q=strchr(s1,s2[i]);
        if (q!=NULL) {
           if (p==NULL) p=q;
           if (q<p) p=q;       
        } 
     }    
        
     return p;
     
}
