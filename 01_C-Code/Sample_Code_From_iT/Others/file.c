#define MAXTITL 20
#define MAXAUTL 30
char title[MAXTITL];
char author[MAXAUTL];
float value;

strcpy(title,"1234567") ;
strcpy(author,"ABCDEFG") ;
value = 1.2f ;

FILE * pbooks
fprintf(pbooks, "%s %s %.2f\n", title, author,value);
==> 1234567 ABCDEFG 1.20 <== 21Byte

fscanf(pbooks,"%s %s %f",title, author,&value);


成功寫入的單位數 = fwrite(title, 1, 4*sizeof (title), pbooks);  ==> 20 Byte
fwrite(author, sizeof (author), 1, pbooks); ==> 30Byte
fwrite(&value, 2/*sizeof (value)*/, 1, pbooks); ==> 6byte
==> 56Byte

成功讀入的單位數 = fread(title, sizeof (title), 1, pbooks) ;


rewind(fp) ==> fseek(fp,0,SEEK_SET) 