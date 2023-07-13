#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char  c1, c2;

  scanf("%c %c", &c1, &c2);
  printf("%d\n", abs(c1 - c2));
  return (0);
}