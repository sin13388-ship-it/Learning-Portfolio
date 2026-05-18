#ifndef AD_HHHH
#define AD_HHHH

#include <stdio.h>


#define MAX_AD_VALUE 1024
#define MAX_VOLTAGE_VALUE 3.3f

#define SAMPLEING_DATA_NO 10

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  场跑计
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 9. 场跑计
//
extern int GlobalVar4 ;

// 10. 硂场跑计compile timeぃ穦Τ岿link穦тぃ
//
extern int GlobalVar3 ;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  PUBLIC Function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float convert_AD_to_Voltage(int AD_Value[],int data_no) ; 


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  PRIVATE Function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float calculate_adv_and_skip2data(int AD_Value[],int data_no) ;


void AD_private_fun_1(void) ;
void AD_private_fun_2(void) ;


#endif
