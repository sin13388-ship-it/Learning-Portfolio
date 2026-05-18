#include <stdio.h>
int output_str(char *string) ;
void To_upper(char *string) ;
void To_lower(char *string) ;
int main(void){

  char names[3][128] = {"abcde\n","fghij\n","Failure starts when you give up\n"};
  /* Practice 
     output_str(names[1]);
     
  */
  
  output_str(names[1]);
  To_upper(names[1]);
  output_str(names[1]);
  To_upper(names[2]);   
  output_str(names[2]);  
  
   output_str("\n--Enjoy---\n");

  getchar();
  return 0;
  
}

void To_lower(char *string)
{
     int i=0;
     
   while (string[i]!='\0' ) 
	 { 
       if (string[i] >='A' && string[i] <='Z') 
        string[i]='a'+(string[i]-'A');
       
        i++;
       
     }    
}

void To_upper(char *string)
{
 
   while (*string!='\0') 
	 { 
        if (*string >='a' && *string<='z') 
        *string='A'+(*string-'a');
        
      
        string++;
        
     }    
}


int output_str(char *string)
{
   // int i=0;
    while(*string!='\0')
    {
       putchar(*string);                  
       string++;
       }
       return 0;
}          




/*

 int output_str(char *string) 
 {
	 int i=0; 
     while (string[i]!='\0') 
	 { putchar(string[i]);
        i++; 
     }
    return i;
} 
*/

