#include "stack.h"
#include <stdio.h>



int main()
{
  Stack stack1 ;
  
  int data[] = {1,2,3,4,5,6,7,8,9,10,11} ;
  int i ;
  int top_data ;

  stack_init(&stack1) ;
  
  for(i=0;i<(11);i++)
			stack_push(&stack1,data[i]);

  printf("Stack length : %d \n",stack_get_length(&stack1)) ;
  
  stack_print_all(&stack1);

  //pop all
  /*
  int pop_data[11];
  stack_pop_all(&stack1,pop_data,11);

  for(i=0;i<(11);i++){
	printf("pop data : %d \n",pop_data[i]) ;
  }
  */

  /*
  for(i=0;i<(11);i++)
	{
		top_data =stack_peek(&stack1) ;
		if(top_data != STACK_EMPTY)
  				printf("peek data : %d \n",top_data) ;
		top_data = stack_pop(&stack1) ;  
  		if(top_data != STACK_EMPTY)
  				printf("pop data : %d \n",top_data) ;
	}

	*/

	// stack should be empty now!
	top_data = stack_pop(&stack1) ;


	return 0;
}
