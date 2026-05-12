#include "dlinklist.h"
#include <stdio.h>
#include <stdlib.h>    // for malloc


/*******************************************
	Method :llist_init
*******************************************/
// Initialize
void llist_init(LinkList * linklist) 
{
	linklist->head = NULL ;
}

/*******************************************
	Method :llist_generate_new_node
*******************************************/
// generate a new node / return NULL if anything wrong
Node * llist_generate_new_node(int value) 
{
	Node * newNode = (Node *)malloc(sizeof(Node)) ;

	if(newNode==NULL) return NULL;


	newNode->data = value ;
	
	newNode->prev = NULL ;
	newNode->next = NULL ;

  // Note: The linked-list module must free this node using 'free()' within an aproppriate
  //function to prevent memory leaks.
  return newNode ;		
}


/*******************************************
	Method :llist_insert_in_front
*******************************************/
// add a new node at the begining of the list
void llist_insert_in_front(LinkList * linklist, Node *newNode) 
{
	  Node * head = linklist->head ;
	  
		if(linklist->head  != NULL)  
	  	(linklist->head )->prev = newNode ;
		newNode->next = head ;
		newNode->prev = NULL ;
		
		linklist->head = newNode ;	
}

/*******************************************
	Method :llist_insert
*******************************************/
// add a new node after a specific node in the list
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) 
{
	Node *cur;

	if(linklist->head=NULL) return;
	if(nodeInList=NULL) return;
	if(newNode=NULL) return;
	cur=linklist->head;
	while(cur !=NULL && (cur!=nodeInList)){
		cur=cur->next;
	}
	if(cur==NULL) return;
	
	if(nodeInList->next != NULL)
			(nodeInList->next)->prev = newNode ;
	
	newNode->next = nodeInList->next ;
	newNode->prev = nodeInList ;
	nodeInList->next = newNode ;
	
}

/*******************************************
	Method :llist_delete_first_node
*******************************************/
// Delete the first node of the list
void llist_delete_first_node(LinkList * linklist) 
{
	Node * tempNodePtr ;
	
	if(linklist->head == NULL)
		return ;		// list is empty
	
	
	tempNodePtr = linklist->head ;
	
	if(tempNodePtr->next != NULL)
		(tempNodePtr->next)->prev = NULL ;
		
	linklist->head = tempNodePtr->next ;
	free(tempNodePtr) ;
	
}



/*******************************************
	Method :llist_delete_node
*******************************************/

// Delete a specific node from the list
void llist_delete_node(LinkList * linklist, Node * nodeInList) 
{
	if(linklist->head == NULL)
		return ;  // empty list

	if( (linklist->head) == nodeInList)
	{
			llist_delete_first_node(linklist) ;	
			return ;
	}

	if(nodeInList->next != NULL)
			(nodeInList->next)->prev = 	(nodeInList->prev) ;
			
	(nodeInList->prev)->next = (nodeInList->next) ;
	
	free(nodeInList) ;
}



/*******************************************
	Method :llist_travel
*******************************************/
// Traverse the list and print all node values
void llist_travel(LinkList * linklist) 
{
	Node * tempNodePtr ;
	tempNodePtr = linklist->head ;
	int index = 1 ;
	
	if(tempNodePtr == NULL)
	{
		printf("list is empty!!\n") ;
		return ;  // empty list
	}
	
	while(tempNodePtr != NULL)
	{
		printf("Node %d, value = %d\n",index++,tempNodePtr->data) ;
		
		tempNodePtr = tempNodePtr->next ;			
	}
	
}

/*******************************************
	Method :llilst_delete
*******************************************/
// Frees all nodes in the list and clears the list.
void llist_delete(LinkList * linklist) 
{
	Node * tempNodePtr ;
	Node * nodeToDel ;
	tempNodePtr = linklist->head ;
	
	if(tempNodePtr == NULL)
		return ;  // empty list
	
	while(tempNodePtr != NULL)
	{
		nodeToDel = tempNodePtr ;
		tempNodePtr = tempNodePtr->next ;			
		
		free(nodeToDel) ;
	}
		
	
}


//*******************************************
// method need to implement:
//*******************************************


/*******************************************
	Method : llist_init2
*******************************************/
// Initializes the list and inserts N nodes from the provided data array
void llist_init2(LinkList * linklist,int * dataArray, int N) 
{
	
	if(dataArray==NULL) return;	
	llist_init(linklist);
	int i;
	for(i=0;i<N;i++){
		Node * newNode= llist_generate_new_node(dataArray[i]);
		if (newNode==NULL) return;
		llist_insert_in_front(linklist,newNode);
	}
}


/*******************************************
	Method : llist_get_last_node
*******************************************/
// Returns the address of the last node in the list.
Node * llist_get_last_node(LinkList * linklist) 
{	
	if(linklist->head==NULL) return NULL;
	Node *cur;
	cur=linklist->head;
	while (cur->next !=NULL)
	{
		cur=cur->next;
	}
	return cur;
}



/*******************************************
	Method : llist_insert_in_rear
*******************************************/
// Appends a new node to the end of the list.
void llist_insert_in_rear(LinkList * linklist, Node *newNode) 
{
	if(newNode==NULL) return;
	Node *cur = llist_get_last_node(linklist);
	cur->next=newNode;
	newNode->prev=cur;
}


/*******************************************
	Method : llist_cat
*******************************************/
//Concatenates list B to the end of list A.
LinkList * llist_cat(LinkList * A, LinkList * B) 
{
	if(A->head==NULL) return B;
	if(B->head==NULL) return A;

	Node *last_node;
	last_node=llist_get_last_node(A);
	last_node->next=B->head;
	B->head->prev=last_node;
	return A;
}


/*******************************************
	Method : llist_get_list_size
*******************************************/
// Returns the total number of nodes in the list
int llist_get_list_size(LinkList * linklist) 
{
	int count=0;

	if (linklist->head==NULL) return 0;

	Node *cur;
	cur=linklist->head;
	while (cur !=NULL)
	{
		count++;
		cur=cur->next;
	}
	return count;

}


/*******************************************
	Method : llist_search
*******************************************/
// Searches for a node with a specific value
// Returns the pointer to the node if found; otherwise, returns NULL
Node * llist_search(LinkList * linklist, int value) 
{
	if(linklist->head==NULL) return NULL;	
	Node *cur;
	cur =linklist->head;
	while(cur!=NULL && (cur->data !=value)){
		cur=cur->next;
	}
	return cur;
}


