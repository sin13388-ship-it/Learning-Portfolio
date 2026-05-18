#include <stdio.h>

//#define XXXX

void recu(int);
int main(void)
{
  recu(1);
  return 0;
}


#ifndef XXXX
void recu(int n)
{
  printf("Level %d\n", n);    /* print #1 */
  if (n < 4)
       recu(n+1);
  printf("LEVEL %d\n", n);    /* print #2 */
}
#endif
