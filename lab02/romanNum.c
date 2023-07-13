#include <stdio.h>

void    roman(int num)
{
        if (num >= 1000)
        {
                putchar('M');
                roman(num - 1000);
        }
        else if (num >= 900)
        {
                printf("CM");
                roman(num - 900);
        }
        else if (num >= 500)
        {
                putchar('D');
                roman(num - 500);
        }
        else if (num >= 400)
        {
                printf("CD");
                roman(num - 400);
        }
        else if (num >= 100)
        {
                putchar('C');
                roman(num - 100);
        }
        else if (num >= 90)
        {
                printf("XC");
                roman(num - 90);
        }
        else if (num >= 50)
        {
                putchar('L');
                roman(num - 50);
        }
        else if (num >= 40)
        {
                printf("XL");
                roman(num - 40);
        }
        else if (num >= 10)
        {
                putchar('X');
                roman(num - 10);
        }
        else if (num >= 9)
        {
                printf("IX");
                roman(num - 9);
        }
        else if (num >= 5)
        {
                putchar('V');
                roman(num - 5);
        }
        else if (num >= 4)
        {
                printf("IV");
                roman(num - 4);
        }
        else if (num > 0)
        {
                putchar('I');
                roman(num - 1);
        }
}

int     main(void)
{
        int     round, num;

        scanf("%d", &round);
        for (int i = 0; i < round; i++)
        {
                scanf("%d", &num);
                roman(num);
                putchar('\n');
        }
        return (0);
}
