#ifndef STACK_HHHH
#define STACK_HHHH


/*******************************************
	Configuration & Limitation
*******************************************/

#define STACK_EMPTY 0xFFFF


/*******************************************
	Data Structure
*******************************************/

// Node structure definition
//
struct node 
{
       int data;
       struct node *next;
};

typedef struct node Node ;



/*A stack can be represented by a node(top) and a length*/ 
struct Stack_s
{ 
 Node * top ;
 int length ; 		// current stack size
}; 

typedef struct Stack_s Stack ;


/*******************************************
	Method Declaration
*******************************************/
void stack_init(Stack * stack) ;

void stack_push(Stack *Stack1,int x) ;

// return STACK_EMPTY if stack empty
int stack_pop(Stack *Stack1) ;

//*******************************************
// method need to implement:
//*******************************************

// 1. check Empty
int stack_empty(Stack *Stack1) ;

// 2. get top element (取出最頂端元素的值，但不做pop的動作)
int stack_peek(Stack *Stack1);

// 3. get element number (目前stack裡有多少個元素)
int stack_get_length(Stack *Stack1);

// 4. pop all  (傳入陣列data[]， data[0]放top的元素, 依此類推)
int stack_pop_all(Stack *Stack1, int *data, int length);


// 5. print all
int stack_print_all(Stack *Stack1);


#endif
