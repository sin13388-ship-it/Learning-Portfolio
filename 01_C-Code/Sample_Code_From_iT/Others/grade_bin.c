char name[30] ;
int ID ;
short grade[3] ;

fwrite(name,1,sizeof(name),fp) ;
fwrite(&ID,1,sizeof(int),fp) ;
fwrite(grade,1,sizeof(grade),fp) ;



int record_size = sizeof(name)+sizeof(int)+sizeof(grade) ;
fseek(fp, record_size*(n-1),SEEK_SET) ;

fread(name,1,sizeof(name),fp) ;
fread(&ID,1,sizeof(int),fp) ;
fread(grade,1,sizeof(grade),fp) ;
