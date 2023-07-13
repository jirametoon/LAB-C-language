#include <stdio.h>
#include <math.h>

float is_hungry(int y, char h)
{
  if (h == 'Y' || h == 'y')
    return (y);
  return (0);
}

float is_sick(int z, char s)
{
  if (s == 'Y' || s == 'y')
    return (z);
  return (1);
}

int main(void)
{
  int   x, y, z;
  char  h, s;

  scanf("%d %d %d", &x, &y, &z);
  scanf(" %c %c", &h, &s);
  printf("%d\n", (int)ceil((x + is_hungry(y, h)) / is_sick(z, s)));
  return (0);
}
