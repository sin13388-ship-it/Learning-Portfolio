#include <stdio.h>
#include <stdlib.h>
void show_usage(char *pro);

int main(int argc, char **argv)
{
 
   char *prog_name=argv[0];
  char *cp;
  if (argc==1) show_usage(argv[0]);
  while (--argc) {
		cp = *++argv;
		if (*cp == '-') {
			++cp;
	
				switch(*cp) {
				case 'o':
					 ++argv; argc--;
					 if (!*argv) { 
						 printf("missing  argument\n") ;
						 show_usage(prog_name);
					 } else
					 printf("has o flag, %s\n",*argv);
					 	
 					 break;

				case 'm':
 					
				        printf("has m flag\n");
                         break;

				case 'n':
 					
				        printf("has n flag\n");
                         break;

				case 'v':
 					
				        printf("has v flag\n");
                          break;                                                                                  
				default: 
				        show_usage(argv[0]);
				

               }

             }


  }
  
  getchar();

return 0;
}


void show_usage(char *pro)
{

   fprintf(stderr,"%s [-m] [-n]  [-v] [-o filename] ",pro);
   exit(0);


}





