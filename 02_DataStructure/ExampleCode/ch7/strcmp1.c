#include <stdio.h>
#include <string.h>
int main(void)
{
  printf("%d\n", strcasecmp("A", "A"));
  printf("%d\n", strcasecmp("A", "B"));
  printf("%d\n", strcasecmp("B", "A"));
  printf("%d\n", strcasecmp("a", "A"));
  printf("%d\n", strcasecmp("Z", "a"));
  printf("%d\n", strcmp("apples", "apple"));
  printf("%d\n", strncmp("apples", "apple",5));
  printf("%d\n", strcasecmp("Apple", "apple"));
  printf("%d\n", strncasecmp("Apple", "apple",5));
 
  getchar();
  return 0;
}
