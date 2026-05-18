#include <stdio.h>

main()
{
 FILE * bin_fp ;
 FILE * txt_fp ;
 
 unsigned int data[4] = {0x1234,0x5678,0xabcd,0xffff} ; 
 
 bin_fp = fopen("binfile","wb") ;
 txt_fp = fopen("txtfile","wt") ;

 // write data to binary file
 fwrite(data,sizeof(int),4,bin_fp) ;
 
 // write string to txt file
 fprintf(txt_fp,"data[0]=%d, data[1]=%d, data[2]=%d, data[3]=%d",
 					data[0],data[1],data[2],data[3]) ;
 
 
 fclose(bin_fp) ;
 fclose(txt_fp) ;
 


/*
 FILE * fp = fopen("memory.jpg","rb") ;
 unsigned char data[1024] ;
 
 fread(data,1,2,fp) ;
 printf("data = %x\n",data[0]) ;
 
 fclose(fp) ;
*/

}
