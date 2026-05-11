#include "linklist.h"
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
  
  // Note： The linked-list module must free this node using 'free()' within an aproppriate
  //function to prevent memory leaks.
  return newNode ;		
}



/*******************************************
	Method :llist_insert_with_sorting
*******************************************/
// Insert with sorting
void llist_insert_with_sorting(LinkList * linklist, Node *newNode) 
{ 	
	Node *cur;
	Node *prev;
	cur=linklist->head;
	prev=NULL;

	if(newNode==NULL) return;

	//Ascending order
	while(cur !=NULL && (cur->data <= newNode->data)){
		prev=cur;
		cur=cur->next;
	}

	//Minimum
	if (prev==NULL){
		llist_insert_in_front(linklist, newNode);
	}else
	{
		llist_insert(linklist,prev,newNode);
	}

	    // 找到第一個比 newNode 大的節點，插在它前面
    // while (cur != NULL && cur->data <= newNode->data) {
    //     prev = cur;
    //     cur = cur->next;
    // }

    // if (prev == NULL) {
    //     // 插在 head 之前（newNode 是最小值，或 list 為空）
    //     newNode->next = linklist->head;
    //     linklist->head = newNode;
    // } else {
    //     // 插在 prev 後面（即 cur 前面）
    //     llist_insert(linklist, prev, newNode);
    // }






}


/*******************************************
	Method :llist_insert_in_front
*******************************************/
// add a new node at the begining of the list
void llist_insert_in_front(LinkList * linklist, Node *newNode) 
{
		newNode->next = (linklist->head) ;
		linklist->head = newNode ;	
}

/*******************************************
	Method :llist_insert
*******************************************/
// add a new node after a specific node in the list
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) 
{
	Node * tempNodePtr;
	
	if (linklist->head==NULL) return;
	if (nodeInList==NULL) return;
	if (newNode==NULL) return;

	tempNodePtr=linklist->head;

	//Ensure that the node is present in the linked-list
	while (tempNodePtr!=NULL)
	{
		if(tempNodePtr==nodeInList) break;
		tempNodePtr=tempNodePtr->next;
	}
	
	if(tempNodePtr==NULL) return;

	newNode->next=nodeInList->next;
	nodeInList->next=newNode;
	
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
	linklist->head = tempNodePtr->next ;
	free(tempNodePtr) ;
	
}



/*******************************************
	Method :llist_delete_node
*******************************************/

// 刪除某個節點
void llist_delete_node(LinkList * linklist, Node * nodeInList) 
{
	Node * tempNodePtr ;
	tempNodePtr = linklist->head ;
	
	if(tempNodePtr == NULL)
		return ;  // empty list
	
	// find the previous Node (singly linked list)	
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
// Initialize a linked list type and insert $N$ nodes consecutively.
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
// Get the last node
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


