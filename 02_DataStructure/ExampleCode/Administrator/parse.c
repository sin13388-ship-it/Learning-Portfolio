/*
http://www.google.com.tw/search?rlz=1C1GPMD_enTW337TW337&sourceid=chrome&q=ABC

1. find '?', 過濾掉"search?" ==> 取得URL & Query String 開頭
2. 尋找'&'，依序找出  "xxx=yyy" 字串
3. 處理每個 "xxx=yyy" 字串，根據'='切割字串

*/

#include <stdio.h>
#include <string.h>

#define QSTR "http://www.google.com.tw/search?hl=zh-TW&source=hp&biw=1024&bih=653&q=book&aq=f&aqi=g10&aql=&oq=&gs_rfai="

// 將Q_sub_string依'='分為兩段，傳回後面那段的位址
//
char * parse_Q_sub_string(char * Q_sub_string) ;

/******************************************************************
	FunctionL main
******************************************************************/
int main()
{
 char string[] = QSTR ;
 char *token ;
 
 char * Q_string ;
 char * right_part_str ;
 
 // get URL ;
 token = strtok(string,"?") ;
 if(token != NULL)
 {
 	//http://www.google.com.tw/search?
 	//  rlz=1C1GPMD_enTW337TW337 0 sourceid=chrome&q=ABC

 		Q_string = token + strlen(token) + 1 ;
 	
 		token[strlen(token)-6] = '\0' ;
 		printf("URL = %s\n",token) ;
 		
 		printf("Query String = %s\n",Q_string) ;
 		
 		// start to parse query-string
 		token = strtok(Q_string,"&") ;
   	while( token != NULL)
  	{
  		right_part_str = parse_Q_sub_string(token) ;
			if(right_part_str != NULL)
			{
					printf("Left = %10s, right = %s\n",token,right_part_str) ;
			}
	   	token=strtok(NULL, "&");
  	}  
		
 }
 
 return 1;
}


//**********************************************************************
// 將Q_sub_string依'='分為兩段，傳回後面那段的位址
//  "xxx 0 yyyyyy"
//**********************************************************************
char * parse_Q_sub_string(char * Q_sub_string) 
{
	int i = 0;
	
	while(Q_sub_string[i] != '=' && Q_sub_string[i] != '\0')
		i++ ;
		
	if(Q_sub_string[i] == '\0')
	{
		return NULL ;
	}
	else
	{
		Q_sub_string[i] = '\0' ;
		return Q_sub_string +i + 1 ;
	}
	
	
}
