#include "Q.h"
#include <stdio.h>

/*******************************************
	Method :
*******************************************/
void queue_init(Queue * queue) 
{
 int i ;
 for(i=0;i<QUEUE_SIZE;i++)
 {
 		queue->Data[i] = 0 ;
 }	

 // front: Immediate data extraction point¡A
 // rear: Immediate data insertion point
 queue->front = -1 ;
 queue->rear = 0 ;
	
}

/*******************************************
	Method :
// return QUEUE_FULL if Q full
*******************************************/
int queue_enqueue(Queue * queue,int x) 
{
		if ( (queue->rear) >= QUEUE_SIZE)
		{
        printf("Queue is full !\n");
        return QUEUE_FULL ;
    }
    else 
	 	{
	 			if(queue->rear == 0)
	 				queue->front = 0 ;		// add the first element
	 				
      	queue->Data[queue->rear] = x ;  
 		  	(queue->rear)++;
    }
	
		return QUEUE_SUCESS ;
}

/*******************************************
	Method : queue_dequeue
// return QUEUE_EMPTY if Q empty
*******************************************/
int queue_dequeue(Queue * queue) 
{
		int data ;
	
		if (queue->front >= queue->rear || queue->front == -1 )
		{
       printf("No item, queue is empty !\n");
       return QUEUE_EMPTY ;
    }
    else 
    {
       data = queue->Data[queue->front] ;
       (queue->front)++;
    }
		
		return data ;	
}

