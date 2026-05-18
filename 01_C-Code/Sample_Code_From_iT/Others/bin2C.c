/*******************************************************************
	Tool – Bin2C.exe
		將xxx.jpg轉為C array，並輸出到xxx.c中
*******************************************************************/
#include <STDIO.H>

main()
{
 FILE * binfp;
 FILE * cfp ;
 unsigned char buffer[1024] ;
 int byte_read = 0 ;
 int i ;

 // 讀者可自行更改輸入，輸出檔名
 //
 binfp = fopen("xxx.jpg","rb") ;
 cfp = fopen("xxx.c","wt") ;
	            
 fprintf(cfp,"//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
 fprintf(cfp,"//\t\tBMP Image as C Array\n") ;
 fprintf(cfp,"//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n") ;
 fprintf(cfp,"//This File is created automaticly \nunsigned char NAME[] = \n{\n") ;

 do
 {
		// 讀出xxx.jpg的內容，並利用fprintf()的功能，將每個byte轉為文字
		//
        byte_read = fread(buffer,1,1024,binfp) ;
        for(i=0;i<byte_read;i++)
        {
                if(buffer[i] <= 0xf)
                       fprintf(cfp,"0x%x ,",buffer[i] );
                else    fprintf(cfp,"0x%x,",buffer[i] );

                if(i%16 == 15)
                        fprintf(cfp,"\n\t") ;
        }

 } while(byte_read == 1024) ;

 fprintf(cfp,"\n} ;\n//end of file") ;

 fclose(binfp) ;
 fclose(cfp) ;

}
