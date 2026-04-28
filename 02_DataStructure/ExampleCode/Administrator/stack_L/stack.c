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
	Method :stack_push
	推入資料
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
	Method : 彈出資料
		- return STACK_EMPTY if stack empty
*******************************************/
int stack_pop(Stack *stack1)
{
	int value ;
	Node * tempNodePtr ;
	
	if(stack1->top == NULL)
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
