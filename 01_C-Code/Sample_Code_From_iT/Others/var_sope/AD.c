
#include "AD.h"

// 11. 场跑计
//
extern int GlobalVar1 ;
extern int GlobalVar2 = 10 ;  //  <== error!!! 场跑计ぃ砞﹚


//12. ぃヴ祘Α郎场跑计
//
extern int variableNoDefind ;	//  comile time pass

/***************************************************************
	Function: convert_AD_to_Voltage
***************************************************************/
float convert_AD_to_Voltage(int AD_Value[],int data_no) 
{
 // 11. 场跑计
 extern int GlobalVar4 ;	
	
 GlobalVar4 = 10 ;
 
 GlobalVar1 = 10 ;
 GlobalVar2 = 10 ;
 
 GlobalVar3 = 10 ;		// <== link time error!!!

 //12. ぃヴ祘Α郎场跑计
 //
 variableNoDefind = 10 ;	// compile time pass, link time error!!!
}


/***************************************************************
	Function: convert_AD_to_Voltage
***************************************************************/
float calculate_adv_and_skip2data(int data[],int data_no) 
{
 // 11. ㄏノ场跑计
 //	

 GlobalVar4 = 10 ;
}


/***************************************************************
	Static Function: AD_private_fun
***************************************************************/

void AD_private_fun_1(void)
{
	...
}

static void AD_private_fun_2(void)
{
	
	...
	
}

