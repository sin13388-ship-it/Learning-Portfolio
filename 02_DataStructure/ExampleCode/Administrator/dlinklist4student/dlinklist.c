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
	

}


/*******************************************
	Method : llist_get_last_node
*******************************************/
// Returns the address of the last node in the list.
Node * llist_get_last_node(LinkList * linklist) 
{
}



/*******************************************
	Method : llist_insert_in_rear
*******************************************/
// �N�s�`�I�[�b��C����
void llist_insert_in_rear(LinkList * linklist, Node *newNode) 
{
}


/*******************************************
	Method : llist_cat
*******************************************/
//���CB���b��CA����
LinkList * llist_cat(LinkList * A, LinkList * B) 
{
 }


/*******************************************
	Method : llist_get_list_size
*******************************************/
// ���o��C���`�I�ƥ�
int llist_get_list_size(LinkList * linklist) 
{
}


/*******************************************
	Method : llist_search
*******************************************/
// �b��C����M�㦳�Y�ӭȪ��`�I
//   YES: return 1,   NO: return 0
Node * llist_search(LinkList * linklist, int value) 
{
 }


