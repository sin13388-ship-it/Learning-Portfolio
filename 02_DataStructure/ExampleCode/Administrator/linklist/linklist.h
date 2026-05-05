#ifndef LINKLIST_HHHH
#define LINKLIST_HHHH

/*******************************************
	Configuration & Limitation
*******************************************/



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


// A linked list can be represented by its head node
//
struct linklist
{
	Node * head ;
} ;

typedef struct linklist LinkList ;

/*******************************************
	Method Declaration
*******************************************/

// generate a new node / return NULL if anything wrong
Node * llist_generate_new_node(int value) ;

// initialize linked list
void llist_init(LinkList * linklist) ;

// <============ one more function
//
// insert node with sorting
void llist_insert_with_sorting(LinkList * linklist, Node *newNod) ;

// 將新節點加在Linked List開頭
void llist_insert_in_front(LinkList * linklist, Node *newNode) ;

// 將新節點加在某個Node之後
void llist_insert(LinkList * linklist,Node * nodeInList,Node *newNode) ;

// 刪除第一個節點
void llist_delete_first_node(LinkList * linklist) ;


// 刪除某個節點
void llist_delete_node(LinkList * linklist, Node * nodeInList) ;

// 印出串列中的所有節點
void llist_travel(LinkList * linklist) ;

// 歸還所有節點
void llist_delete(LinkList * linklist) ;



//*******************************************
// method need to implement:
//*******************************************

// 初始化 linklist型別, 並直接insert N個節點
void llist_init2(LinkList * linklist,int * dataArray, int N) ;


// 取得串列最後一個Node的位址
Node * llist_get_last_node(LinkList * linklist) ;

// 將新節點加在串列結尾
void llist_insert_in_rear(LinkList * linklist, Node *newNode) ;

//把串列B接在串列A之後
LinkList * llist_cat(LinkList * A, LinkList * B) ;

// 取得串列的節點數目
int llist_get_list_size(LinkList * C) ;

// 在串列中找尋具有某個值的節點
//   return Node if found   else return 0
Node * llist_search(LinkList * linklist, int value) ;




#endif
