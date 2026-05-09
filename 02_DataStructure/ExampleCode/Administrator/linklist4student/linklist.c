#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>    // for malloc


/*******************************************
	Method :llist_init
*******************************************/
// initialize linked list
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

	if (newNode==NULL)
	{
		return NULL;
	}	

	newNode->data = value ;
	newNode->next = NULL ;

  // Note： The linked-list module must free this node using 'free()' within an aproppriate
  //function to prevent memory leaks.
  return newNode ;		
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
// Delete the first node of the list
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

// Delete a specific node from the list
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
		
		// 注意free的時機
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
	//Initialize
	llist_init(linklist);

	if(dataArray==NULL || N <=0) return;

	Node *tail; //找尾巴
	for(int i=0; i<N; i++){
		Node *tempNodePtr =	llist_generate_new_node(dataArray[i]);
		if(tempNodePtr==NULL) return;
		if(linklist->head==NULL){			
			linklist->head=tempNodePtr;
			tail=tempNodePtr; //head 同時也是最末端
		}
		else{
			tail->next=tempNodePtr; //接上
			tail=tempNodePtr; //更新尾巴的位置
		}

	}
}


/*******************************************
	Method : llist_get_last_node
*******************************************/
// 取得串列最後一個Node的位址
Node * llist_get_last_node(LinkList * linklist) 
{
	Node *cur;

	if ( linklist->head ==NULL)
	{
		return NULL;
	}	
	cur=linklist->head;
	while(cur->next!=NULL){
		cur=cur->next;
	}
	return cur;

}

/*******************************************
	Method : llist_insert_in_rear
*******************************************/
// 將新節點加在串列結尾
void llist_insert_in_rear(LinkList * linklist, Node *newNode) 
{
	Node *last ;	
	last=llist_get_last_node(linklist);
	if(last==NULL){
		linklist->head=newNode;
	}
	else{
		last->next=newNode;		
	}
	newNode->next=NULL;
}


/*******************************************
	Method : llist_cat
*******************************************/
//把串列B接在串列A之後
LinkList * llist_cat(LinkList * A, LinkList * B) 
{
	//考慮各別為NULL的情形
	if(A->head==NULL) return B;
	if(B->head==NULL) return A;

	Node * tail;
	tail=llist_get_last_node(A);
	tail->next=B->head;
	return A;
}


/*******************************************
	Method : llist_get_list_size
*******************************************/
// 取得串列的節點數目
int llist_get_list_size(LinkList * linklist) 
{
	int length=0;
	if(linklist->head==NULL) return 0;
	Node *cur;
	cur=linklist->head;
	while (cur !=NULL)
	{
		length++;
		cur=cur->next;
	}
	return length;
	
}


/*******************************************
	Method : llist_search
*******************************************/
// 在串列中找尋具有某個值的節點
//   YES: return 1,   NO: return 0
Node * llist_search(LinkList * linklist, int value) 
{
	if(linklist->head==NULL) return NULL;	
	Node *cur;
	cur=linklist->head;
	while (cur !=NULL)
	{
		if(cur->data==value) break;
		cur=cur->next;
	}
	return cur;
}


