#include <stdio.h>
#include <stdlib.h>

#define SIZE (1024*1024)

#define PATTERN1 0xaa
#define PATTERN2 0x55
#define PATTERN3 0xFF

// return 0 if error
int verify_memory_block(unsigned char * start_address,
												unsigned int size,unsigned char pattern) ;

//return checksum
unsigned long calculate_checksum(unsigned char * start_address,unsigned int size) ;



/***************************************************************
	Function: main
***************************************************************/
main()
{
 unsigned char * start_address ;

 
 start_address = (unsigned char *)malloc(MEMORY_SIZE) ;
 if(start_address == NULL)
 {
 		printf("allocate memory error!\n") ; 	
 		return ;
 }
 
 // memory verifiction
 if(!verify_memory_block(start_address,MEMORY_SIZE,PATTERN1))
 {
 		printf("pattern1 testing error\n") ; 	
 		return ;
 }

 if(!verify_memory_block(start_address,MEMORY_SIZE,PATTERN2))
 {
 		printf("pattern2 testing error\n") ; 	
 		return ;
 }

 if(!verify_memory_block(start_address,MEMORY_SIZE,PATTERN3))
 {
 		printf("pattern3 testing error\n") ; 	
 		return ;
 }


 // calculate checksum
 printf("checksum = %d\n",calculate_checksum(start_address,MEMORY_SIZE)) ;
 
 
 free(start_address) ;
}


/***************************************************************
	Function: convert_AD_to_Voltage
		return0 if error
***************************************************************/
int verify_memory_block(unsigned char * org_start_address,
												unsigned int size,unsigned char pattern)
{
	int i ;
	
	unsigned long long_pattern = 0 ;
	unsigned long * start_address = (unsigned long *)org_start_address ;
	
	if(pattern == PATTERN1)
		long_pattern = 0x55555555 ;
	else if(pattern == PATTERN2)
		long_pattern = 0xaaaaaaaa ;

	printf("writing data...\n") ;
	
	// write data pattern to memoy
	for(i=0;i<(size>>2);i++)
	{
		if(pattern == PATTERN3)
		{
			unsigned long temp = (unsigned long)(start_address+i) ;
			long_pattern = temp & 0x0F ;
			long_pattern = (long_pattern + ((temp+1) & 0x0F) << 8) ;
			long_pattern = (long_pattern + ((temp+2) & 0x0F) << 16) ;
			long_pattern = (long_pattern + ((temp+3) & 0x0F) << 24) ;
		}

		start_address[i] = long_pattern ;		
	}
	
	// read out data and verify
	printf("verify data...\n") ;
	
	// write data pattern to memoy
	for(i=0;i<(size>>2);i++)
	{
		if(pattern == PATTERN3)
		{
			unsigned long temp = (unsigned long)(start_address+i) ;
			long_pattern = temp & 0x0F ;
			long_pattern = (long_pattern + ((temp+1) & 0x0F) << 8) ;
			long_pattern = (long_pattern + ((temp+2) & 0x0F) << 16) ;
			long_pattern = (long_pattern + ((temp+3) & 0x0F) << 24) ;
		}
		
		if(start_address[i] != long_pattern)
		{
				return 0 ;
		}

	}

	printf("Verification done!\n") ;
	return 1 ;
	
}

/***************************************************************
	Function: convert_AD_to_Voltage
		return checksum
***************************************************************/
unsigned long calculate_checksum(unsigned char * start_address,unsigned int size) 
{
 int i ;	
 unsigned long checksum =0 ;
 
 for(i=0;i<size;i++)
 	checksum += start_address[i] ;
 	
 return checksum ;		
	
}



