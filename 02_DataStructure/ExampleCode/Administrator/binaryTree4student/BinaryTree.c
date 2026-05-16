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
