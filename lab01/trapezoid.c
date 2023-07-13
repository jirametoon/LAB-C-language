#include <stdio.h>

int main(void)
{
  int a,b,h;
  float res;

  printf("a : ");
  scanf("%d", &a);
  printf("b : ");
  scanf("%d", &b);
  printf("h : ");
  scanf("%d", &h);
  res = 0.5 * (a + b) * h;
  printf("Area is %.1f\n", res);
  return (0);
 }
