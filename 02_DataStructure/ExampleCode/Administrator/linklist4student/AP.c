#include "linklist.h"
#include <stdio.h>

main()
{
 LinkList myList1 ;
  
 Node *newNode ;
 Node *newNode2 ;

 llist_init(&myList1) ;

 printf("\n[Testing1]\n") ;
 llist_travel(&myList1) ;
 
 // create and insert some node
 newNode = llist_generate_new_node(1) ;
 llist_insert_in_front(&myList1,newNode) ;
 
 newNode = llist_generate_new_node(2) ;
 llist_insert_in_front(&myList1,newNode) ;
 
 newNode = llist_generate_new_node(3) ;
 llist_insert_in_front(&myList1,newNode) ;

 printf("\n[Testing2]\n") ;
 llist_travel(&myList1) ;
 
 llist_delete_first_node(&myList1) ;
 printf("\n[Testing3] - delete 1st Node\n") ;
 llist_travel(&myList1) ;
 

 // add 3 more Nodes
 newNode = llist_generate_new_node(4) ;
 llist_insert_in_front(&myList1,newNode) ;
 
 newNode2 = llist_generate_new_node(5) ;
 llist_insert_in_front(&myList1,newNode2) ;
 
 newNode = llist_generate_new_node(6) ;
 llist_insert_in_front(&myList1,newNode) ;

 // delete some node
 printf("\n[Testing4] - before delete a Node\n") ;
 llist_travel(&myList1) ;
 
 printf("\n[Testing4] - after delete a Node\n") ;
 llist_delete_node(&myList1,newNode2) ;
 llist_travel(&myList1) ;

/*
// 由學生負責實作
{ 
 LinkList myList2 ;
 LinkList * myList3 ;
 
 Node * nodeToDel ;
 Node * lastNode ;
 
 int data[5] = {100,101,102,103,104} ;
 	
 // test 5  - myList2  (init list with some nodes) 
 printf("\n[Test 5]\n") ;
 llist_init2(&myList2,data,5) ; 
 llist_travel(&myList2) ;
 
 // test 5-2: get last node and show its value
 //
 lastNode = llist_get_last_node(&myList2) ;
 printf("\n[Test5-2]: last value of myList2 is %d",lastNode->data) ;
 

 // test 6 - 把一個Node加在 myList2 尾端
 //
 printf("\n[Test 6]\n") ;
 newNode = llist_generate_new_node(1024) ;
 llist_insert_in_rear(&myList2,newNode) ;
 llist_travel(&myList2) ;

 // test 7 - 把list2加在list1尾巴, 印出新串列與其節點數目
 printf("\n[Test 7]\n") ;
 myList3 = llist_cat(&myList1,&myList2) ;
 llist_travel(myList3) ;

 printf("list number = %d\n",llist_get_list_size(myList3)) ;

 
 // test 8 - 在新串列中尋找第一個值為"2"的節點,並將其刪除
 printf("\n[Test 8]\n") ;
 nodeToDel = llist_search(myList3,2) ;
 if(nodeToDel == NULL)
 		printf("cannot find node ith value 2\n") ;
 else
 {
 		llist_delete_node(myList3,nodeToDel) ;
 		llist_travel(myList3) ;
 }
	
 //llist_delete(&myList2) ;
		
 }
 */
 llist_delete(&myList1) ;
  
}
