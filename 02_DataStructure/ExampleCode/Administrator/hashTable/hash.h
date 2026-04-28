#ifndef HASH_HHHH
#define HASH_HHHH

#include "linklist.h"

/*******************************************
	Configuration & Limitation
*******************************************/

#define HASH_TABLE_ENTRY_NO 32

/*******************************************
	Data Structure
*******************************************/

// 節點資料結構定義
//
struct hashtable 
{
       LinkList list[HASH_TABLE_ENTRY_NO] ;
};

typedef struct hashtable HashTable ;



/*******************************************
	Method Declaration
*******************************************/

void hash_init(HashTable * hashTable) ;

// key: student name
// return: index of hash table (0~HASH_TABLE_ENTRY_NO-1)
int hash_function(char * student_name) ;

void hash_add_student(HashTable * hashTable, Student * student_info) ;

// this function would save data in parameter "student_info"
// return 0 if not found, else return 1
//
int hash_search(HashTable * hashTable, Student * toFind, Student * found) ;


//*******************************************
// method need to implement:
//*******************************************


#endif
