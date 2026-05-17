#include "BinaryTree.h"
#include <stdio.h>

int main()
{
 BinTree tree ;
 BinTree subTree ;
 Node * node ;
 
 int i ;
 int data[10] = {23,34,56,123,12,2,65,67,23,1234} ;
 
 binTree_init(&tree) ;
 
 for(i=0;i<10;i++)
 		tree.root = binTree_add_new_node(&tree,data[i]) ;

 //<=======================
 printf("\n[test1] Inorder travel\n") ;
 binTree_travel(&tree) ;
 
 //<=======================
 printf("\n\n[test2] Deepth = %d \n",binTree_treeDeepth(&tree)) ;
 
 //<=======================
 printf("\n\n[test3] postorder travel\n") ;
 binTree_travel_postorder(&tree) ;
 
 //<=======================
 printf("\n\n[test4] preorder travel\n") ;
 binTree_travel_preorder(&tree) ;
 
 //<=======================
 printf("\n\n[test5] Max data is : %d\n",binTree_get_Max(&tree)) ;
  
 printf("\n\n[test5] Min data is : %d\n",binTree_get_Min(&tree)) ;
 
 //<=======================
 printf("\n\n[test6] search data 78 \n") ;
 node = binTree_search(&tree,78) ;
 if(node == NULL)
 		printf("cannot find! \n") ;
 else
 		printf("find data %d\n",node->data) ;

 //<=======================
 printf("\n\n[test6] search data 123 \n") ;
 node = binTree_search(&tree,123) ;
 if(node == NULL)
 		printf("cannot find! \n") ;
 else
 		printf("find data %d\n",node->data) ;

 subTree.root = node ; 
 printf("its deepth = %d \n",binTree_treeDeepth(&subTree)) ;
 		
 //<=======================
 printf("\n\n[test7] item 34's sibling is: \n") ;
 node = binTree_search(&tree,34) ; 		
 node = binTree_get_sibling(&tree,node) ;		
 printf("sibling data = %d\n",node->data) ;

  //<=======================
 printf("\n\n[test8] item 1234's sibling is: \n") ;
 node = binTree_search(&tree,1234) ; 		
 node = binTree_get_sibling(&tree,node) ;		
 printf("sibling data = %d\n",node->data) ;
 
 binTree_free(&tree);
return 0;
 
}
