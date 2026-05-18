#include "my_fs.h"
#include <stdlib.h>



/******************************************************
	Global Variable
******************************************************/
#ifdef PC_SIMULATION
	unsigned char * ROM_start_address = NULL ;
#else
	#define ROM_start_address 0x10000	
#endif

struct FS_table * ROM_FS_table = NULL ;

struct file_info * File_info_list = NULL ;


/******************************************************
	Function :fs_load_rom_image
		return 0 if something wrong
******************************************************/
// 將rom.img載入記憶體模擬ROM, 並紀錄start address
int fs_load_rom_image(void) 
{
	struct FS_table fs_table ;
	
	FILE * fp = fopen(ROM_FILE_NAME,"rb") ;		
	if(fp == NULL)
		return 0 ;
	
	fread(&fs_table,sizeof(struct FS_table),1,fp) ;
	printf("\nfile number = %d, ROM size = %d\n",fs_table.file_number,fs_table.ROM_size) ;
	
	
	// allocate memory
	ROM_start_address = (unsigned char *)malloc(fs_table.ROM_size) ;
	if(ROM_start_address == NULL)
		return 0 ;
	
	fseek(fp,0,SEEK_SET) ;	
	fread(ROM_start_address,1,fs_table.ROM_size,fp) ;	
	
	fclose(fp) ;
	return 1 ;
}


/******************************************************
	Function :fs_free_rom_image
******************************************************/
// 歸還模擬ROM的記憶體
void fs_free_rom_image(void) 
{
 free(ROM_start_address) ;	
	
}


/******************************************************
	Function :fs_init
******************************************************/
// 設定檔案系統表格
void fs_init(void) 
{
ROM_FS_table = (struct FS_table * )ROM_start_address ;
File_info_list = (struct file_info *)(ROM_start_address + sizeof(struct FS_table)) ;

}



/******************************************************
	Function :fs_list_all_file_name
******************************************************/
void fs_list_all_file_info(void) 
{
 int file_no = ROM_FS_table->file_number ;
 int i ;
 
 for(i=0;i<file_no;i++)	
		printf("%s - size = %d, offset = %d\n",
				File_info_list[i].name,File_info_list[i].size,File_info_list[i].offset) ;
	
}

/******************************************************
	Function :fs_open
		return -1 if open error
******************************************************/

char *File_base_address = NULL ;
int File_pointer = 0 ;

// return file handle (i.e. file_info table 的index)
int fs_open(char * filename) 
{
 int file_no = ROM_FS_table->file_number ;
 int i ;
 
 for(i=0;i<file_no;i++)	
 {
		if(strcmp(File_info_list[i].name,filename) == 0)
		{
				File_base_address = (char *)(ROM_start_address + File_info_list[i].offset) ;
				File_pointer = 0 ;
				return i ;
		} 	
 }
	
 return -1 ;		
}




/******************************************************
	Function :fs_show_file_info
******************************************************/
void fs_show_file_info(int handle) 
{
	
		printf("%s - size = %d, offset = %d\n",
				File_info_list[handle].name,File_info_list[handle].size,File_info_list[handle].offset) ;
	
}

/******************************************************
	Function :fs_read_data
******************************************************/
// 循序讀，傳回讀出的byte數
// 傳回-1表示已經到檔尾
//
int fs_read_data(int handle,char *buffer,int read_size)  
{
	int i ;
	int file_size =  File_info_list[handle].size ;
	
	if(File_pointer >= file_size)
			return -1 ;

	
	if(	(File_pointer + read_size) > file_size)
	{
		read_size -= ((File_pointer + read_size) - file_size) ;
	}

	for(i=0;i<read_size;i++)
	{
			buffer[i] = File_base_address[File_pointer++] ;			
	}
	
	return read_size ;
	
}


