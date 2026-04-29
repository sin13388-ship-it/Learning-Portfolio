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
     return 0; /* 空樹深度為0 */
     
   if(root->left != NULL)
   {
   	 subTree.root = root->left ; 
     left_deepth=binTree_treeDeepth(&subTree); /* left_deepth為左子樹的深度 */
   }
   else
     left_deepth=0;
     
   if(root->right != NULL)
   {
   	 subTree.root = root->right ; 
     right_deepth=binTree_treeDeepth(&subTree); /* right_deepth為右子樹的深度 */
   }
   else
     right_deepth=0;
   
   /* T的深度為其左右子樹的深度中的大者+1 */	  
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

/*******************************************
	Method :binTree_travel_postorder
*******************************************/
void binTree_travel_postorder(BinTree * tree) 
{
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


/*******************************************
	Method :binTree_travel_preorder
*******************************************/
void binTree_travel_preorder(BinTree * tree) 
{
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


/*******************************************
	Method :binTree_get_Max
*******************************************/
int binTree_get_Max(BinTree * tree) 
{
 Node * root = tree->root ;

 BinTree subTree ;	
	
 int value ; 
 
 if(root == NULL)
 	return 0xFFFF ;
 
 value = root->data ; 
 
 if(root->right != NULL)
 {
 		subTree.root = root->right ; 	
 		value = binTree_get_Max(&subTree) ;	
 }	
 
 return value ;

}


/*******************************************
	Method :binTree_get_Min
*******************************************/
int binTree_get_Min(BinTree * tree) 
{
 Node * root = tree->root ;
 BinTree subTree ;	
	
 int value  ;
 
 if(root == NULL)
 	return 0xFFFF ;
 
 value = root->data ;
 
 if(root->left != NULL)
 {
 		subTree.root = root->left ; 	
 		value = binTree_get_Min(&subTree) ;	
 }	
 
 return value ;
	
	
}


/*******************************************
	Method :binTree_search
*******************************************/
Node * binTree_search(BinTree * tree,int value) 
{
 Node * root = tree->root ;
 BinTree subTree ;
 
 	if(root == NULL)
 		return NULL ;
 	
 	if(root->data == value)
 		return root ;
 		
 	if(value > root->data)
 	{
 		subTree.root = root->right ;
 		return binTree_search(&subTree,value) ;
 	}
 	else
 	{
 		subTree.root = root->left ;
 		return binTree_search(&subTree,value) ;
 	}
 	
 		
}

/*******************************************
	Method :binTree_get_sibling
*******************************************/
Node * binTree_get_sibling(BinTree * tree, Node * node) 
{
	Node * parent ;
	
	parent = node->parent ;
	if(parent == NULL)
		return NULL ;
		
	if(parent->left == node)
		return (parent->right) ;
	else
		return parent->left ;
	
}
