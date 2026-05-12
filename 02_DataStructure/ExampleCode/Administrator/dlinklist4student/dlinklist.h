#ifndef DLINKLIST_HHHH
#define DLINKLIST_HHHH

/*******************************************
	Configuration & Limitation
*******************************************/



/*******************************************
	Data Structure
*******************************************/

// Node definition for doubly linked-list
//
struct node 
{
       int data;
       struct node *next;
       struct node *prev;
};

typedef struct node Node ;


// Using a node to represent a linked-list
//
struct linklist
{
	Node * head ;
} ;

typedef struct linklist LinkList ;

/*******************************************
	Method Declaration
*******************************************/

// generate a new node / return NULL if anything wrong
Node * llist_generate_new_node(int value) ;

// Inititalize 
void llist_init(LinkList * linklist) ;

// add a new node in the front of the list
void llist_insert_in_front(LinkList * linklist, Node *newNode) ;

// add a new node after a specific node in the list
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) ;

// delete the first node of the list
void llist_delete_first_node(LinkList * linklist) ;


// delete a node from the list
void llist_delete_node(LinkList * linklist, Node * nodeInList) ;

// Traverses the list and prints all node values
void llist_travel(LinkList * linklist) ;

// Frees all nodes in the list and clears the list
void llist_delete(LinkList * linklist) ;



//*******************************************
// method need to implement:
//*******************************************

// Initializes the list and inserts N nodes from the provided data array
void llist_init2(LinkList * linklist,int * dataArray, int N) ;


// Returns the address of the last node in the list.
Node * llist_get_last_node(LinkList * linklist) ;

// Appends a new node to the end of the list.
void llist_insert_in_rear(LinkList * linklist, Node *newNode) ;

//Concatenates list B to the end of list A.
LinkList * llist_cat(LinkList * A, LinkList * B) ;

// Returns the total number of nodes in the list
int llist_get_list_size(LinkList * C) ;

// Searches for a node with a specific value
// Returns the pointer to the node if found; otherwise, returns NULL
Node * llist_search(LinkList * linklist, int value) ;



#endif
