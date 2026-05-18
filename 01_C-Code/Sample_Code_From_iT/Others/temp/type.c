#pragma pack(1)

struct mp3_header
{
	unsigned char header_id[3] ;
	unsigned char version[2] ;
	unsigned char flag ;
	unsigned long size ;
	unsigned long frame_header_id ;

 ...
} ;


main()
{
	FILE * fp ;
	struct mp3_header header ;
	
	fp = fopen("xxx.mp3","rb") ;
	fread(&header,sizeof(struct mp3_header),1,fp) ;
	
	printf("header id = %c%c%c",header.header_id[0],header.header_id[1],header.header_id[2]) ;	
	
	fclose(fp) ;
	
}


#pragma pack()


#pragma pack(1)
typedef struct{
	char	tagid[3];//0-2  TAG identifier. It contains of string "ID3" 
	short	tagverm	;//3-4  TAG version
	char	flags	;//5	Flags 
	long	size	;//6-9  Size of TAG MSB
} MP3ID3TAG2;

int unpacktagsize(MP3ID3TAG2 id){
	int a, b, c, d;
	a = id.size & 0x7f000000,
	b = id.size & 0x007f0000,
	c = id.size & 0x00007f00,
	d = id.size & 0x0000007f;
	return	a>>3 | b>>2 | c>>1 | d>>0;
}






double pam(int);
double pam2(int);
double pam3(int);

		double y ;
    double (*pf) (int);
    pf=pam;
    y = (*pf) (5) ;  // == > y = pam(5) ;
    
    pf = pam2 ;
    y = (*pf) (100) ;  // == > y = pam2(100) ;
    

int * ptr ;
int A, B ;

ptr = &A ;
(*ptr) = 5 ;

ptr = &B ;
(*ptr) = 10 ;   



typedef double (*FUN)(int,float);

typedef int MYINT ;







printf("%d %x",pow(2,3),pow) ;
printf("%d",8) ;




struct LCD_mode_reg
{
	unsigned int bit_per_pix : 3 ;
	unsigned int rev : 1 ;
	unsigned int LUT : 1 ;
	unsigned int rev2: 1 ;
	unsigned int dither_mode:1 ;
	unsigned int frame_rep: 1 ;	
} ;

struct LCD_mode_reg *ptr ;
ptr = (struct LCD_mode_reg *)0x380200 ;
ptr->bit_per_pix = 3 ;





enum tag_field {female,male} ; 

union type3
{
			int children;
			int beard;
} ;

struct type1 
{
   enum tag_field sex;  
	 union type3 u;
} ;

typedef struct type1 sex_type ;


struct  type2
{
     char name[10];
     int age;
     float salary;
     sex_type sex_info;			
} ;

typedef struct type2 human_being  ;


human_being persion1,persion2;

persion1.sex_info.sex=male;
Persion1.sex_info.u.beard=TRUE;

persion2.sex_info.sex=female;
Persion2.sex_info.u.children=TRUE;
