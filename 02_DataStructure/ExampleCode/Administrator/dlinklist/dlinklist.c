#include "dlinklist.h"
#include <stdio.h>
#include <stdlib.h>    // for malloc


/*******************************************
	Method :llist_init
*******************************************/
// 初始化 linklist型別
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

  // 注意： LinkList模組勢必要在某個method內將此node歸還 (free())
  return newNode ;		
}


/*******************************************
	Method :llist_insert_in_front
*******************************************/
// 將新節點加在Linked List開頭
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
// 將新節點加在某個Node之後
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) 
{
	// 判斷 nodeInList 確實存在list裡
	// todo
	
	if(nodeInList->next != NULL)
			(nodeInList->next)->prev = newNode ;
	
	newNode->next = nodeInList->next ;
	newNode->prev = nodeInList ;
	nodeInList->next = newNode ;
	
}

/*******************************************
	Method :llist_delete_first_node
*******************************************/
// 刪除第一個節點
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

// 刪除某個節點
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
// 印出串列中的所有節點
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
// 歸還所有節點
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
		
	linklist->head = NULL ;
}


//*******************************************
// method need to implement:
//*******************************************


/*******************************************
	Method : llist_init2
*******************************************/
// 初始化 linklist型別, 並直接insert N個節點
void llist_init2(LinkList * linklist,int * dataArray, int N) 
{
 Node * newNode ;	
 int i ;
  
 llist_init(linklist) ;
 
 for(i=0;i<N;i++)
 {
	 newNode = llist_generate_new_node(dataArray[i]) ;
	 llist_insert_in_front(linklist,newNode) ;
 }

}


/*******************************************
	Method : llist_get_last_node
*******************************************/
// 取得串列最後一個Node的位址
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
// 將新節點加在串列結尾
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
//把串列B接在串列A之後
LinkList * llist_cat(LinkList * A, LinkList * B) 
{
 Node * last_node = llist_get_last_node(A) ;		
 
 last_node->next = (B->head) ;
 (B->head)->prev = last_node ;
 
 return A ;
}


/*******************************************
	Method : llist_get_list_size
*******************************************/
// 取得串列的節點數目
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
// 在串列中找尋具有某個值的節點
//   YES: return 1,   NO: return 0
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


