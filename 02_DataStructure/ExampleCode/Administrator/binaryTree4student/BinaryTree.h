#ifndef BINARY_TREE_HHHH
#define BINARY_TREE_HHHH

/*******************************************
	Configuration & Limitation
*******************************************/


/*******************************************
	Data Structure
*******************************************/

/* 二叉樹的二叉鏈表存儲表示 */
 struct node
 {
   int data;
   struct node *left,*right; /* 左右孩子指針 */
   
   struct node * parent ;
 };

typedef struct node Node ;

struct binary_tree
{
	Node * root ;
} ;

typedef struct binary_tree BinTree ;

/*******************************************
	Method Declaration
*******************************************/
void binTree_init(BinTree * tree) ;

Node * binTree_add_new_node(BinTree * tree, int value) ;

void binTree_travel(BinTree * tree) ;  // inorder

int binTree_treeDeepth(BinTree * tree) ;

Node * binTree_parent(BinTree * tree,Node * child) ;


//*******************************************
// method need to implement:
//*******************************************

void binTree_travel_postorder(BinTree * tree) ;
void binTree_travel_preorder(BinTree * tree) ;

int binTree_get_Max(BinTree * tree) ;
int binTree_get_Min(BinTree * tree) ;

Node * binTree_search(BinTree * tree,int value) ;

Node * binTree_get_sibling(BinTree * tree, Node * node) ;




#endif
