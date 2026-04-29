#include <stdio.h>
#include "my_fs.h"

main()
{
 int i ;	
 int handle ;	
 int result = -1 ;
 char buffer[1000+1] ;
	
 fs_load_rom_image() ;
 fs_init() ;
  
 // list all file
 fs_list_all_file_info() ;
 
 // read out "d.c" and list its content 	
 handle = fs_open("e.html")  ;
 if(handle == -1 )
 {
 		printf("open file error!\n") ;	
 		return ;
 }
 
 fs_show_file_info(handle) ;
 
 printf("\n\nprint e.html: \n") ;
 
 
 do
 {
 	 result = fs_read_data(handle,buffer,1000) ;

	 if(result != -1)
	 {
	 		buffer[result] = '\0' ;
	 		printf("%s",buffer) ;
	 	}
	} while(result == 1000) ;
 
 fs_free_rom_image() ;	
}

