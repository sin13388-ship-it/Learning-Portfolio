#include "CircularQ.h"
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

 // front: 馬上可以抓走資料的位置，
 // rear: 馬上可以塞入資料的位置
 queue->front = -1 ;
 queue->rear = 0 ;
	
}

/*******************************************
	Method :
// return QUEUE_FULL if Q full
*******************************************/
int queue_enqueue(Queue * queue,int x) 
{
		static int first_time_flag = 0 ;
		if(first_time_flag == 0)
		{
			queue->front = 0 ;	
			first_time_flag = 1 ;
		}
	
		if ( (queue->front) == (queue->rear + 1) % QUEUE_SIZE)
		{
        printf("Queue is full !\n");
        return QUEUE_FULL ;
    }
    else 
	 	{
      	queue->Data[queue->rear] = x ;  
 		  	queue->rear = (queue->rear + 1) % QUEUE_SIZE ;
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
	
		if (queue->front == queue->rear || queue->front == -1 )
		{
       printf("No item, queue is empty !\n");
       return QUEUE_EMPTY ;
    }
    else 
    {
       data = queue->Data[queue->front] ;
       (queue->front)= (queue->front + 1) % QUEUE_SIZE ;
    }
		
		return data ;	
}

