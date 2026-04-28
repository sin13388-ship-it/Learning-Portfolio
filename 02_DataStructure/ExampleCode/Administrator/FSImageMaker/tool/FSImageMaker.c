#include <stdio.h>
#include <stdlib.h>
#include "../my_fs.h"


#define ROM_IMAGE_FILE "rom.img"
#define FILE_LIST "file.list"

void file_cat(char * file1, char *file2) ;

/**********************************************************
	Function: main
**********************************************************/
main()
{
	int i ;
	FILE * rom_fp ;	
	FILE * list_fp ;
	FILE * data_fp ;
	
	struct FS_table fs_table ;
	int file_number = 0 ;
	char temp_file_name[20] ;
	
	struct file_info * file_info_list ;
	int file_offset = 0 ;

	// 先讀出file.list的內容，並計算檔案數目
	list_fp = fopen(FILE_LIST,"rt") ;
	while( fscanf(list_fp,"%s",temp_file_name) == 1)
		file_number++ ;	
	
	printf("Total File Number = %d\n",file_number) ;		
	
		
	// 配置 file_info table 的空間
	file_info_list = (struct file_info * ) malloc(sizeof(struct file_info)*file_number) ;
	if(file_info_list == NULL)
	{
		printf("memory allocate error\n") ;
		fclose(list_fp) ;
		return ;
	}
	
	// 先讀出所有檔案的資訊，建立file system表格
	fseek(list_fp,0,SEEK_SET) ;
	file_offset = sizeof(struct FS_table) + file_number * sizeof(struct file_info) ;
	
	for(i=0;i<file_number;i++)
	{
		int data_file_size ;
		
		fscanf(list_fp,"%s",file_info_list[i].name) ;
		
		// open data file and get it's size
		data_fp = fopen(file_info_list[i].name,"rb") ;
		if(data_fp == NULL)
		{
				// file not exist
				file_info_list[i].size = 0 ;	
				file_info_list[i].offset = file_offset ; 
		}
		else
		{
				fseek(data_fp,0,SEEK_END) ;			
				data_file_size = ftell(data_fp) ;
				fclose(data_fp) ;
				
				file_info_list[i].size = data_file_size ;
				file_info_list[i].offset = file_offset ; 
				file_offset += data_file_size ;
		}
		
		printf("%s - size = %d, offset = %d\n",
				file_info_list[i].name,file_info_list[i].size,file_info_list[i].offset) ;
	}
  
  fclose(list_fp) ;
	
	// 填入FS table的欄位
	fs_table.file_number = file_number ;
	fs_table.ROM_size = file_offset ;
	printf("ROM image size should be : %d \n",fs_table.ROM_size) ;
	
	// 將file system table寫到rom.img
	rom_fp = fopen(ROM_IMAGE_FILE,"wb") ;
	
	fwrite(&fs_table,sizeof(struct FS_table) , 1, rom_fp) ;
	fwrite(file_info_list,sizeof(struct file_info) , file_number, rom_fp) ;
	
	fclose(rom_fp) ;

	// 將data file陸續連接到rom.img的尾端
	for(i=0;i<file_number;i++)
		file_cat("rom.img",file_info_list[i].name) ;


 free(file_info_list) ;


}


/**********************************************************
	Function: file_cat
**********************************************************/
void file_cat(char * file1, char *file2)
{
	// file2被接續在file1之後
	FILE * fp1 ;
	FILE * fp2 ;
	unsigned char buffer[1024] ;
	int result ;
	
	fp1 = fopen(file1,"ab") ;
	fp2 = fopen(file2,"rb") ;
	
	fseek(fp1,0,SEEK_END) ;
	
	do
	{
			result = fread(buffer,1,1024,fp2) ;		
			fwrite(buffer,1,result,fp1) ;
	} while(result == 1024) ;
	
	fclose(fp1) ;
	fclose(fp2) ;
}
