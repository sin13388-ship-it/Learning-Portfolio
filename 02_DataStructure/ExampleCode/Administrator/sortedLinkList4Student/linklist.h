#ifndef LINKLIST_HHHH
#define LINKLIST_HHHH

/*******************************************
	Configuration & Limitation
*******************************************/



/*******************************************
	Data Structure
*******************************************/

// Node definition
//
struct node 
{
       int data;
       struct node *next;
};

typedef struct node Node ;


// a linked-list can be represented by a node (head)
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

// Initializes linked-list
void llist_init(LinkList * linklist) ;

// <============ one more function
//
// Insert a new node with sorting
void llist_insert_with_sorting(LinkList * linklist, Node *newNod) ;

// Insert a new node at the beginning of the list
void llist_insert_in_front(LinkList * linklist, Node *newNode) ;

// Insert a new node after a specific node in the list
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) ;

// Deletes the first node of the list.
void llist_delete_first_node(LinkList * linklist) ;


// Deletes a specific node from the list.
void llist_delete_node(LinkList * linklist, Node * nodeInList) ;

// Traverses the list and prints all node values.
void llist_travel(LinkList * linklist) ;

// Frees all nodes in the list and clears the list.
void llist_delete(LinkList * linklist) ;



//*******************************************
// method need to implement:
//*******************************************

// ��l�� linklist���O, �ê���insert N�Ӹ`�I
void llist_init2(LinkList * linklist,int * dataArray, int N) ;


// Returns the address of the last node in the list.
Node * llist_get_last_node(LinkList * linklist) ;

// Appends a new node to the end of the list.
void llist_insert_in_rear(LinkList * linklist, Node *newNode) ;

// Concatenates list B to the end of list A.
LinkList * llist_cat(LinkList * A, LinkList * B) ;

// Returns the total number of nodes in the list.
int llist_get_list_size(LinkList * C) ;

// Searches for a node with a specific value. 
// Returns the pointer to the node if found; otherwise, returns NULL.
Node * llist_search(LinkList * linklist, int value) ;



#endif
