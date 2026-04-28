#include "Q.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************
	Method :
*******************************************/
void queue_init(Queue * queue) 
{
	// 一個node不儲存資料
	Node * headNode = (Node *)malloc(sizeof(Node)) ;	
	
	queue->front = headNode ;
	queue->rear = headNode ;
	
	headNode->next = NULL ;
		
}

/*******************************************
	Method :
// return QUEUE_FULL if Q full
*******************************************/
int queue_enqueue(Queue * queue,int value) 
{
	Node * newNode ;
	
	newNode = (Node *)malloc(sizeof(Node)) ;	
	if(newNode == NULL)
		return QUEUE_FULL ;
	
	newNode->data = value ;
	newNode->next = NULL ;
	
	(queue->rear)->next = newNode ;
	queue->rear = newNode ;
	
	return QUEUE_SUCESS ;
}

/*******************************************
	Method : queue_dequeue
// return QUEUE_EMPTY if Q empty
*******************************************/
int queue_dequeue(Queue * queue) 
{
		Node * dequeuedNode ;
		int value ;
		
		if((queue->front) == (queue->rear))
		{
       printf("No item, queue is empty !\n");
       return QUEUE_EMPTY ;
    }

		dequeuedNode = (queue->front)->next ;
		value = dequeuedNode->data ;
		(queue->front)->next = dequeuedNode->next ;
		
		if(queue->rear == dequeuedNode)
			(queue->rear) = (queue->front) ;
			
		free(dequeuedNode) ;
		
		return value ;
}
	