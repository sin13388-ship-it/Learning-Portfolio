#ifndef FS_API_HHH
#define FS_API_HHH

#include <stdio.h>

/******************************************************
	CONSTANT
******************************************************/
#define ROM_FILE_NAME "rom.img"

#define PC_SIMULATION

/******************************************************
	Data Structure
******************************************************/
struct file_info
{
	char name[12] ;
	int offset ;
	int size ;	
	
} ;

struct FS_table
{
	int file_number ;
	int ROM_size ;
} ;



/******************************************************
	Function Declaration
******************************************************/

#ifdef PC_SIMULATION

	// 將rom.img載入記憶體模擬ROM, 並紀錄start address
	// return 0 if something wrong
	int fs_load_rom_image(void) ;
	
	// 歸還模擬ROM的記憶體
	void fs_free_rom_image(void) ;

#endif


// 設定檔案系統表格
void fs_init(void) ;

// return file handle (i.e. file_info table 的index)
int fs_open(char * filename) ;

void fs_list_all_file_info(void) ;
void fs_show_file_info(int handle) ;

// 循序讀，傳回讀出的byte數
// 傳回-1表示已經到檔尾
//
int fs_read_data(int handle,char *buffer,int size) ;



#endif

