







int a ;
struct aaa
{
 char a[10] ;
 int b ;

} ;

long C[100] ;

int size = sizeof(a/*變數*/) ;
int size = sizeof(int/*型別*/) ;
int size = sizeof(struct aaa/*結構*/) ;
int size = sizeof(long/*陣列*/) * 100 ;


FILE * fp = fopen("xxx.jpg","rb") ;
unsigned char byte ;
int data[10] ;


fread(位置,單位大小,多少個單位, 檔案) ;
fread(&byte,sizeof(char),1,fp) ;

fread(data,sizeof(int),10,fp) ;