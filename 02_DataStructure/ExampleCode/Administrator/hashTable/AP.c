#include "hash.h"
#include <stdio.h>
#include <string.h>

main()
{
 int i,result ;	
 HashTable hashTable ;	
 Student searchResult ;
 Student searchPattern ;
 
 Student student[7] =  {
 		{"John",12},
 		{"Tom Cheng",20},
 		{"Mary Chiu",8},
 		{"Michael Jodarn",40},
 		{"Lady Gaga",30},
 		{"Michael JacksonII",30},
 		{"Lady Gaga",20},
 	} ;

 hash_init(&hashTable) ;	
	
 for(i=0;i<7;i++)	
 		hash_add_student(&hashTable,&(student[i])) ;
 
 result = hash_search(&hashTable,&(student[3]),&searchResult) ; 
 if(result == 1)
 		printf("\nFound student - %s, age = %d \n",searchResult.name,searchResult.age) ;
 else
 		printf("\ncannot found\n") ;

 strcpy(searchPattern.name,"Ealin Chiu") ;
 searchPattern.age = 39 ;
 result = hash_search(&hashTable,&searchPattern,&searchResult) ; 
 if(result == 1)
 		printf("\nFound student - %s, age = %d \n",searchResult.name,searchResult.age) ;
 else
 		printf("\ncannot found\n") ;

}
