#include "linklist.h"
#include <stdio.h>

main()
{
 LinkList myList1 ;
 Node *newNode ;

 int data[10] = {10,3,40,100,23,33,10,23,34,1203} ;
 int i ;

 llist_init(&myList1) ;

 for(i=0;i<10;i++)
 {
		 newNode = llist_generate_new_node(data[i]) ;
		 llist_insert_with_sorting(&myList1,newNode) ;
 }

 llist_travel(&myList1) ;
  
 
 llist_delete(&myList1) ;
  
}

