#include "Q.h"
#include <stdio.h>

main()
{
 Queue Q ;
 int data[10] ;
 int i ;
 
 A =10 ;
 
 queue_init(&Q) ;
 
 // testing : dequeue from empty Q
 printf("\n[test1]: testing : dequeue from empty Q\n") ;
 data[0] = queue_dequeue(&Q) ;
 
 // testing : enqueue 8 items, then dequeue 6 items
 printf("\n[test2]: enqueue 8 items, then dequeue 6 items\n") ;
 queue_enqueue(&Q,1) ;
 queue_enqueue(&Q,2) ;
 queue_enqueue(&Q,3) ;
 queue_enqueue(&Q,4) ;
 queue_enqueue(&Q,5) ;
 queue_enqueue(&Q,6) ;
 queue_enqueue(&Q,7) ;
 queue_enqueue(&Q,8) ;
 
 for(i=0;i<6;i++)
 {
 		data[i] = queue_dequeue(&Q) ;	
 		if(data[i] != QUEUE_EMPTY)
 			printf("Q[%d] = %d\n",i,data[i]) ;
 }
 
 // testing : enqueue 3 items, then dequeue 6 items
 printf("\n[test3]: enqueue 3 items, then dequeue 6 items\n") ;
 queue_enqueue(&Q,9) ;
 queue_enqueue(&Q,10) ;
 queue_enqueue(&Q,11) ;
 for(i=0;i<6;i++)
 {
 		data[i] = queue_dequeue(&Q) ;	
 		if(data[i] != QUEUE_EMPTY)
 			printf("Q[%d] = %d\n",i,data[i]) ;
 }
 
 // testing : try to enqueue something again
 printf("\n[test4]: try to enqueue something again\n") ;
 if( queue_enqueue(&Q,9) != QUEUE_SUCESS)
 		printf("we cannot use this Queue any more!\n") ;
  else
  	printf("Enqueue OK!") ;
}
