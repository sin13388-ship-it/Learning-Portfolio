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
