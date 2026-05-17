#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

/*******************************************
	Method :binTree_init
*******************************************/
void binTree_init(BinTree * tree) 
{
	tree->root = NULL ;	
}


/*******************************************
	private Method : binTree_create_new_node
*******************************************/
static Node * binTree_create_new_node(int value)
{
	Node * newNode ;
	
	newNode = (Node *)malloc(sizeof(Node)) ;	
	if(newNode == NULL)
		return NULL ;
		
	newNode->left = NULL ;
	newNode->parent = NULL ;
	newNode->right = NULL ;
	
	newNode->data = value ;
	
	return newNode ;
}

/*******************************************
	Method : returm address of root Node
	return root Node
*******************************************/
Node * binTree_add_new_node(BinTree * tree, int value) 
{
	Node * newNode ;
	Node * root ;
	
	BinTree subTree ;

	root = tree->root ;
	
	if(root == NULL)
	{
			newNode = binTree_create_new_node(value) ;
			return newNode ;
	} 	
	else if(value > root->data)
	{
		  subTree.root = root->right ;

			root->right = binTree_add_new_node(&subTree,value) ;		
			(root->right)->parent = root ;
			return root ;
	}
	else
	{
		  subTree.root = root->left ;

			root->left = binTree_add_new_node(&subTree,value) ;		
			(root->left)->parent = root ;
			return root ;
	}
}

/*******************************************
	Method : binTree_travel   (inorder)
*******************************************/
void binTree_travel(BinTree * tree) 
{
		BinTree subTree ;
		Node * root = tree->root ;
		
		
		if(root != NULL)
		{
			subTree.root = root->left ;
			binTree_travel(&subTree) ;			
			
			printf("%d ",root->data) ;
			
			subTree.root = root->right ;
			binTree_travel(&subTree) ;			
		}
}

/*******************************************
	Method :binTree_treeDeepth
*******************************************/
int binTree_treeDeepth(BinTree * tree) 
{
   int left_deepth,right_deepth;
   BinTree subTree ;
   Node * root = tree->root ;
   
 
   if(root== NULL) 
     return 0; /* the depth of an empty tree is 0 */
     
   if(root->left != NULL)
   {
   	 subTree.root = root->left ; 
     left_deepth=binTree_treeDeepth(&subTree); /* left_depth is the depth of the left subtree */
   }
   else
     left_deepth=0;
     
   if(root->right != NULL)
   {
   	 subTree.root = root->right ; 
     right_deepth=binTree_treeDeepth(&subTree); /* right_depth is the depth of the right subtree */
   }
   else
     right_deepth=0;
   
   /* the depth of T is the larger of its left and right subtree depths plus 1 */	  
   return (left_deepth>right_deepth)?left_deepth+1:right_deepth+1; 
}

/*******************************************
	Method :binTree_parent
*******************************************/
Node * binTree_parent(BinTree * tree,Node * child) 
{
	if(tree != NULL && child != NULL)
		return child->parent ;
	else
		return NULL ;
}


//<<----------------------------------------------------------------------------
//
//
//
//*******************************************
// method need to implement:
//*******************************************

//*******************************************
// method : binTree_travel_postorder
// left -> right -> center
//*******************************************

void binTree_travel_postorder(BinTree * tree){

		BinTree subTree ;
		Node * root = tree->root ;
		
		
		if(root != NULL)
		{
			subTree.root = root->left ;
			binTree_travel_postorder(&subTree) ;	
			
			subTree.root = root->right ;
			binTree_travel_postorder(&subTree) ;
			
			printf("%d ",root->data) ;			
			
		}


}

//*******************************************
// method : binTree_travel_preorder
// center -> left -> right
//*******************************************

void binTree_travel_preorder(BinTree * tree){

		BinTree subTree ;
		Node * root = tree->root ;
		
		
		if(root != NULL)
		{
			printf("%d ",root->data) ;
			
			subTree.root = root->left ;
			binTree_travel_preorder(&subTree) ;	
			
			subTree.root = root->right ;
			binTree_travel_preorder(&subTree) ;		

		}

}


//*******************************************
// method : binTree_get_Max
//*******************************************

int binTree_get_Max(BinTree * tree){

		BinTree subTree ;
		Node * root = tree->root ;
				
		int rightData;
		
		if(root->right!= NULL)
		{		
			subTree.root = root->right ;
			rightData=binTree_get_Max(&subTree) ;
		}
		else rightData=root->data;				

	return rightData;
}

//*******************************************
// method : binTree_get_Min
//*******************************************

int binTree_get_Min(BinTree * tree){

		BinTree subTree ;
		Node * root = tree->root ;
				
		int leftData;
		
		if(root->left!= NULL)
		{		
			subTree.root = root->left ;
			leftData=binTree_get_Min(&subTree) ;
		}
		else leftData=root->data;				

	return leftData;
}

//*******************************************
// method : sub method for  binTree_search
//*******************************************
Node *search_Node(Node * root, int value){

	if (root ==NULL || root->data==value) return root;	

	if(root->data < value){
		 return search_Node(root->right,value);
	}

	else{
		return search_Node(root->left,value);
	}

}

//*******************************************
// method : binTree_search
//*******************************************
Node * binTree_search(BinTree * tree,int value){

	if(tree==NULL) return NULL;
	
	Node *root= tree->root;

	return search_Node(root, value);
}
//*******************************************
// method : binTree_get_sibling
//*******************************************
Node * binTree_get_sibling(BinTree * tree, Node * node)
{
	if(tree==NULL) return NULL;
	Node *parent;
	parent=binTree_parent(tree,node);
	if(parent->left==node) return parent->right;
	else return parent->left;
}

//*******************************************
// method : free_Node, sub method for binTree_free
//*******************************************

void free_Node(Node * root){

	if (root==NULL) return;
	free_Node(root->right);
	free_Node(root->left);
	free(root);
}

//*******************************************
// method :binTree_free
//*******************************************

void binTree_free(BinTree *tree){
	if (tree==NULL) return;
	free_Node(tree->root);
	tree->root=NULL; //clear pointer
}