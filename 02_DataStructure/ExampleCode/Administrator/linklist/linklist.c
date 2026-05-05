#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>    // for malloc


/*******************************************
	Method :llist_init
*******************************************/
// ��l�� linklist���O
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

  // �`�N�G LinkList�Ҳնե��n�b�Y��method���N��node�k�� (free())
  return newNode ;		
}


/*******************************************
	Method :llist_insert_in_front
*******************************************/
// �N�s�`�I�[�bLinked List�}�Y
void llist_insert_in_front(LinkList * linklist, Node *newNode) 
{
		newNode->next = (linklist->head) ;
		linklist->head = newNode ;	
}

/*******************************************
	Method :llist_insert
*******************************************/
// �N�s�`�I�[�b�Y��Node����
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) 
{
	// �P�_ nodeInList �T��s�blist��
	// todo
	
	newNode->next = nodeInList->next ;
	nodeInList->next = newNode ;
	
}

/*******************************************
	Method :llist_delete_first_node
*******************************************/
// �R���Ĥ@�Ӹ`�I
void llist_delete_first_node(LinkList * linklist) 
{
	Node * tempNodePtr ;
	
	if(linklist->head == NULL)
		return ;		// list is empty
	
	tempNodePtr = linklist->head ;
	linklist->head = tempNodePtr->next ;
	free(tempNodePtr) ;
	
}



/*******************************************
	Method :llist_delete_node
*******************************************/

// �R���Y�Ӹ`�I
void llist_delete_node(LinkList * linklist, Node * nodeInList) 
{
	Node * tempNodePtr ;
	tempNodePtr = linklist->head ;
	
	if(tempNodePtr == NULL)
		return ;  // empty list
	
	// find the previous Node (�]���u�����᭱��link)	
	while(tempNodePtr != NULL)
	{
			if(tempNodePtr->next == nodeInList)
			{
					// got it!
					tempNodePtr->next = nodeInList->next ;
					free(nodeInList) ;
					break ;
			}		
			else
			{
					tempNodePtr = tempNodePtr->next ;	
			}
		
	}
	
}



/*******************************************
	Method :llist_travel
*******************************************/
// �L�X��C�����Ҧ��`�I
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
// �k�٩Ҧ��`�I
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
		
		// �`�Nfree���ɾ�
		free(nodeToDel) ;
	}
		
	linklist->head = NULL ;
}


//*******************************************
// method need to implement:
//*******************************************


/*******************************************
	Method : llist_init2
*******************************************/
// ��l�� linklist���O, �ê���insert N�Ӹ`�I
void llist_init2(LinkList * linklist,int * dataArray, int N) 
{
 Node * newNode ;	
 int i ;
  
 llist_init(linklist) ;
 
 for(i=0;i<N;i++)
 {
	 newNode = llist_generate_new_node(dataArray[i]) ;
	 llist_insert_in_front(linklist,newNode);
 }

}


/*******************************************
	Method : llist_get_last_node
*******************************************/
// ���o��C�̫�@��Node����}
Node * llist_get_last_node(LinkList * linklist) 
{
 Node * tempNodePtr ;
 Node * currentNodePtr ;
 
 tempNodePtr = linklist->head ;
 
 while(tempNodePtr != NULL)
 {
		currentNodePtr = tempNodePtr ; 	
 		tempNodePtr = tempNodePtr->next ;
 }	

 return currentNodePtr ;	
}



/*******************************************
	Method : llist_insert_in_rear
*******************************************/
// �N�s�`�I�[�b��C����
void llist_insert_in_rear(LinkList * linklist, Node *newNode) 
{
 Node * last_node = llist_get_last_node(linklist) ;	
 llist_insert(linklist,last_node,newNode) ;
 
 // by pointer access
 /*
 last_node->next = newNode ;
 newNode->next = NULL ;
 */
}


/*******************************************
	Method : llist_cat
*******************************************/
//���CB���b��CA����
LinkList * llist_cat(LinkList * A, LinkList * B) 
{
 Node * last_node = llist_get_last_node(A) ;		
 
 last_node->next = (B->head) ;
 
 return A ;
}


/*******************************************
	Method : llist_get_list_size
*******************************************/
// ���o��C���`�I�ƥ�
int llist_get_list_size(LinkList * linklist) 
{
 int counter = 0 ;
 Node * tempNodePtr ;
 
 tempNodePtr = linklist->head ;
 
 while(tempNodePtr != NULL)
 {
 		counter++ ;	
 		tempNodePtr = tempNodePtr->next ;
 }

 return counter ; 	
}


/*******************************************
	Method : llist_search
*******************************************/
// �b��C����M�㦳�Y�ӭȪ��`�I
//   return Node if found   else return NULL
Node * llist_search(LinkList * linklist, int value) 
{
 Node * tempNodePtr ;
 
  
 tempNodePtr = linklist->head ;
 
 while(tempNodePtr != NULL)
 {
		if(tempNodePtr->data == value)
		{
			return tempNodePtr ;	
		}
 		tempNodePtr = tempNodePtr->next ;
 }

 return NULL ;
}


