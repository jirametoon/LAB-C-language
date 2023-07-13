#include <stdio.h>

int main(void)
{
  unsigned int time;
  int day, hrs, min, sec;

  scanf("%u", &time);
  day = ((time / 60) / 60) / 24;
  hrs = ((time / 60) / 60) - (day * 24);
  min = (time / 60) - (day * 24 * 60) - (hrs * 60);
  sec = time % 60;
  printf("%u %u %u %u\n", day, hrs, min, sec);
  return (0);
}
