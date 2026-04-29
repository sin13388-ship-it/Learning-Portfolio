#include "AD.h"

// 1. global variable (其他 .c 檔也可以用)
int GlobalVar1 ;
int GlobalVar2 ;

// 2. static global variable (只有這個.c 檔內可以用)
static int GlobalVar3 ;


/****************************************************************
	Function: Main
****************************************************************/
main()
{
 // local 變數  ==> 只有在大括號範圍內可以用	
	
 //3. local varible (or auto variable, 在進入大括號執行時, 才指定變數的位址)
 // 	
 int AD[SAMPLEING_DATA_NO] = {700,732,680,500,820,702,693,717,704,699}  ;
 float voltage ;
 int i ;
 
 // 4. staic local variable (非auto變數, 在程式開始執行時即已指定變數位址)
 //
 static int staticLocalVariable = 0 ;  // <== 初始化只做一次
 
 if(staticLocalVariable == 0)
 {
 			// do some initialization
 			//...
 			staticLocalVariable =0  ;
 }
 
 for(i=0;i<10;i++)
 {
 		// 5. local/auto variable
 		int x = 100 ;
 		//
 		// do something...	
 	
 }
 
 // you cannot access x here!!
 
 {
 		// 6. local/auto variable
 		int x = 10 ;
 		
 		{
 				// x again!
 				int x = 20 ;
 				// ...
 		}
 		
 		// 現在x等於多少？ x=10
 }

 // you cannot access x here!!


 // 7. I can access "GlobalVar1", "GlobalVar2", "GlobalVar3" 
 //    in all functions in this file
 GlobalVar1 = 10 ;
 GlobalVar2 = 20 ;
 GlobalVar3 = 30 ;
 
 // 8. but I cannot access "GlobalVar5" here!
 //
 
 
 // 9. I can access "GlobalVar4" because it's described as external variable
 GlobalVar4 = 100 ;


}


/****************************************************************
	Function: sub
****************************************************************/
// 全域變數
//
int GlobalVar4 ;
int GlobalVar5 ;

void sub()
{
 extern void AD_private_fun_1(void) ;	
 extern void AD_private_fun_2(void) ;	
	
 // 7. I can access "GlobalVar1", "GlobalVar2", "GlobalVar3" 
 //    in all functions in this file
 GlobalVar1 = 10 ;
 GlobalVar2 = 20 ;
 GlobalVar3 = 30 ;

 // 8. I can access "GlobalVar4" here!
 GlobalVar4 = 20 ;
 GlobalVar5 = 30 ;
	
	
 // 13. call external function
 //
 AD_private_fun_1() ;			// OK
 AD_private_fun_2() ;			// compile time error
	
	
}
