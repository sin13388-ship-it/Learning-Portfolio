/*
Goal:

	輸入一個圓的半徑，計算後輸出圓的周長。
	C = 2*PI*r ;
*/

#include <stdio.h>


main()
{
 // input r
 // opout C
 float r ;	// 半徑
 float C ;	// 週長
 
 const float PI = 3.1415926 ;
 
 printf("Please input R: \n") ;
 
 // ask user input r
 scanf("%f",&r) ;
 	
 C = 2 * PI * r ;	
 
 printf("C = %10.2f \n",C) ;
	
	
}

