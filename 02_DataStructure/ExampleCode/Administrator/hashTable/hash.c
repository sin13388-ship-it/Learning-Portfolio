#include "hash.h"
#include <stdio.h>
#include <stdlib.h>    // for malloc
#include <string.h>


/*******************************************
	Method :hash_function
*******************************************/
void hash_init(HashTable * hashTable) 
{
 int i ;
 
 for(i=0;i<HASH_TABLE_ENTRY_NO;i++)
 		llist_init(&(hashTable->list[i])) ;	
}


/*******************************************
	Method :hash_function
*******************************************/
// key: student name
// return: index of hash table (0~HASH_TABLE_ENTRY_NO-1)
int hash_function(char * student_name) 
{
 unsigned int sum = 0;
 int index = 0 ;	
 	
 while(student_name[index] != '\0')	
 {
 		sum = sum + student_name[index] ;
 		index++ ;
 }

 return (sum & 0x1F) ;		// mod 32 / (sum % 32)
}
// 0x1F = 0001 1111


/*******************************************
	Method :hash_add_student
*******************************************/
void hash_add_student(HashTable * hashTable,Student * student_info) 
{
 Node * newNode ;	
	
 int index = hash_function(student_info->name) ;	
 
 newNode = llist_generate_new_node(0) ;
 llist_set_student_info(newNode,student_info) ;
 
 // add to list
 llist_insert_in_front(&(hashTable->list[index]),newNode) ;	

printf("add student -%s (age = %d) in list#%d\n",student_info->name,student_info->age,index) ;
	
}

/*******************************************
	Method :hash_search
*******************************************/
// this function would save data in parameter "student_info"
// return 0 if not found, else return 1
//
int hash_search(HashTable * hashTable,Student * toFind, Student * found) 
{
 Node * node ;	
	
 int index = hash_function(toFind->name) ;	
 LinkList * list = &(hashTable->list[index]) ;	
	
 node = llist_search_student(list,toFind) ;	
 if(node != NULL)
 {
 		strcpy(found->name,node->student.name) ;
 		found->age = node->student.age ;
 		return 1 ;
 }
 else
 		return 0 ;
}
