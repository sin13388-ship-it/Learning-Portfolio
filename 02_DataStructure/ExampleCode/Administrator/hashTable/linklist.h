#ifndef LINKLIST_HHHH
#define LINKLIST_HHHH

#include "student.h"

/*******************************************
	Configuration & Limitation
*******************************************/



/*******************************************
	Data Structure
*******************************************/

// Node definition add student
//
struct node 
{
			 int data ;
			 Student student;
       
       struct node *next;
};

typedef struct node Node ;


// using a node to represent a linke-list
//
struct linklist
{
	Node * head ;
} ;

typedef struct linklist LinkList ;

/*******************************************
	New Function for access Student's data
*******************************************/
void llist_set_student_info(Node * node, Student * student_info)  ;

Node * llist_search_student(LinkList * linklist, Student * student_info) ;




/*******************************************
	Method Declaration
*******************************************/

// generate a new node / return NULL if anything wrong
Node * llist_generate_new_node(int value) ;

// intialize
void llist_init(LinkList * linklist) ;

// add a new node in the begining of the list
void llist_insert_in_front(LinkList * linklist, Node *newNode) ;

// insert a node after a specific node in the list
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) ;

// delete the first node
void llist_delete_first_node(LinkList * linklist) ;


// delete a node after a specific node from the list
void llist_delete_node(LinkList * linklist, Node * nodeInList) ;

// print all nodes
void llist_travel(LinkList * linklist) ;

// free nodes
void llist_delete(LinkList * linklist) ;



//*******************************************
// Method need to implement:
//*******************************************

// Initialize linklist type and directly insert N nodes
void llist_init2(LinkList * linklist,int * dataArray, int N) ;


// Get the address of the last node in the list
Node * llist_get_last_node(LinkList * linklist) ;

// Insert a new node at the end of the list
void llist_insert_in_rear(LinkList * linklist, Node *newNode) ;

// Concatenate list B after list A
LinkList * llist_cat(LinkList * A, LinkList * B) ;

// Get the number of nodes in the list
int llist_get_list_size(LinkList * C) ;

// Search for a node with a specific value in the list
//   YES: return 1,   NO: return 0
Node * llist_search(LinkList * linklist, int value) ;



#endif
