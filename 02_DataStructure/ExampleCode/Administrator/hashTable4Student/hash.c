#include "hash.h"
#include <stdio.h>
#include <stdlib.h>    // for malloc
#include <string.h>


/*******************************************
	Method :hash_function
*******************************************/
void hash_init(HashTable * hashTable) 
{
}


/*******************************************
	Method :hash_function
*******************************************/
// key: student name
// return: index of hash table (0~HASH_TABLE_ENTRY_NO-1)
int hash_function(char * student_name) 
{
}



/*******************************************
	Method :hash_add_student
*******************************************/
void hash_add_student(HashTable * hashTable,Student * student_info) 
{
	
}

/*******************************************
	Method :hash_search
*******************************************/
// this function would save data in parameter "student_info"
// return 0 if not found, else return 1
//
int hash_search(HashTable * hashTable,Student * toFind, Student * found) 
{
}
