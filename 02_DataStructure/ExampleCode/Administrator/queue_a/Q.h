#ifndef QUEUE_HHHH
#define QUEUE_HHHH

/*******************************************
	Configuration & Limitation
*******************************************/
#define QUEUE_SIZE 10

#define QUEUE_EMPTY 0xFFFF
#define QUEUE_FULL  0xFFFE

#define QUEUE_SUCESS 1
/*******************************************
	Data Structure
*******************************************/

/*Queue資料結構*/ 
struct queue_s
{ 
	int Data[QUEUE_SIZE];		//陣列空間 
	int front, rear;								
													// front: dequeue，
 													// rear: enqueue
}; 

typedef struct queue_s Queue ;


/*******************************************
	Method Declaration
*******************************************/
void queue_init(Queue * queue) ;

// return QUEUE_FULL if Q full
int queue_enqueue(Queue * queue,int x) ;

// return QUEUE_EMPTY if Q empty
int queue_dequeue(Queue * queue) ;



//*******************************************
// method need to implement:
//*******************************************

void queue_reset(Queue * queue) ;

#endif
