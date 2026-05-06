#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************
	Method :stack_init
*******************************************/
void stack_init(Stack * stack)
{
 stack->top = NULL ;
 stack->length = 0 ;
}

/*******************************************
	Method :stack_empty
	return STACK_EMPTY if stack empty
*******************************************/
int stack_empty(Stack *Stack1)
{
	return (Stack1->top) ==NULL;
}

/*******************************************
	Method :stack_peek
	return STACK_EMPTY if stack empty
*******************************************/
int stack_peek(Stack *Stack1){
	
	if(stack_empty(Stack1))
  {
    printf("stack is empty\n");
    return STACK_EMPTY ;
  }
  else
  {
	 return (Stack1->top)->data ; 	
  }
 
}

/*******************************************
	Method :stack_get_length	
*******************************************/
int stack_get_length(Stack *Stack1){
	return Stack1->length;
}

/*******************************************
	Method :stack_pop_all
	return error if array length is not equal to stack length
*******************************************/
int stack_pop_all(Stack *Stack1, int *data, int length){

  //check
  if(Stack1->length != length) {
	printf("Length error!\n");
	return -1;
  }
  int i=0;
  while (!stack_empty(Stack1))
  {
	data[i++]=stack_pop(Stack1);
  }
  return 0;
}

/*******************************************
	Method :stack_print_all
	return STACK_EMPTY if stack empty
*******************************************/
int stack_print_all(Stack *Stack1){
  if(stack_empty(Stack1))
  {
    printf("stack is empty\n");
    return STACK_EMPTY ;
  }
  else
  {
	 int i;
	 Node * tempNodePtr ;
	 tempNodePtr=Stack1->top;
	
	 for(i=0; i< Stack1->length; i++){
		
		printf("%d : %d \n", i, (tempNodePtr)->data);
		tempNodePtr=tempNodePtr->next;
	 }	
	 return 0;
  }
}

/*******************************************
	Method :stack_push
	push data into stack
*******************************************/

void stack_push(Stack *stack1,int x)
{
 Node * p = (Node *)malloc(sizeof(Node)) ;	
 
 p->data = x ;
 p->next = stack1->top ;	
 stack1->top = p ;
 (stack1->length)++ ;
 
}


/*******************************************
	Method : ¼u¥X¸ê®Æ
		- return STACK_EMPTY if stack empty
*******************************************/
int stack_pop(Stack *stack1)
{
	int value ;
	Node * tempNodePtr ;
	
	if(stack_empty(stack1))
  {
    printf("stack is empty\n");
    return STACK_EMPTY ;
  }
  else
  {
		value = (stack1->top)->data ;
		tempNodePtr = stack1->top ;
		(stack1->top) = (stack1->top)->next ;
		(stack1->length)-- ;
		
		free(tempNodePtr) ;
 	
  }
	
  return value ;	
         
}
