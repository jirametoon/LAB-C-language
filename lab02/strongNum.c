#include <stdio.h>

int     factorial(int n)
{
        int     res;

        res = 1;
        for (int i = 1; i <= n; i++)
                res *= i;
        return (res);
}

int     cal_fact_digit(int n)
{
        if (n > 9)
                return (cal_fact_digit(n % 10) + cal_fact_digit(n / 10));
        else
                return (factorial(n % 10));
}

int     strongNum(int num)
{
        for (int i = num - 1; i > 0; i--)
        {
                if (cal_fact_digit(i) == i)
                        return (i);
        }
        return (1);
}

int     main(void)
{
        int     round, num;

        scanf("%d", &round);
        for (int i = 0; i < round; i++)
        {
                scanf("%d", &num);
                printf("%d\n", strongNum(num));
        }
        return (0);
}
