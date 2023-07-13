#include <stdio.h>

int main(void)
{
  int x, y;

  scanf("%d %d", &x, &y);
  printf("%d %d\n", (y + x) / 24, (y + x) % 24);
  return (0);
}
