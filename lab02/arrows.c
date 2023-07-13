#include <stdio.h>

void    print(char c, int round)
{
        for (int i = 0; i < round; i++)
                putchar(c);
}

void    north(int size)
{
        int     sp, i;

        sp = size;
        for (i = 0; i <= size; i++, sp--)
        {
                print(' ', sp);
                print('#', (2 * i) + 1);
                putchar('\n');
        }
        for (i = 0; i <= size; i++)
        {
                putchar(' ');
                print('#', (2 * size) - 1);
                putchar('\n');
        }
}

void    south(int size)
{
        int     sp, i;

        sp = 0;
        for (i = 0; i <= size; i++)
        {
                putchar(' ');
                print('#', (2 * size) - 1);
                putchar('\n');
        }
        for (i = size; i >= 0; i--, sp++)
        {
                print(' ', sp);
                print('#', (2 * i) + 1);
                putchar('\n');
        }
}

void    east(int size)
{
        int     i;

        for (i = 1; i <= size + 1; i++)
        {
                if (i == 1)
                {
                        print(' ', size + 1);
                        printf("#\n");
                }
                else
                {
                        print('#', size + 1);
                        print('#', i);
                        putchar('\n');
                }
        }
        for (i = size; i > 0; i--)
        {
                if (i == 1)
                {
                        print(' ', size + 1);
                        printf("#\n");
                }
                else
                {
                        print('#', size + 1);
                        print('#', i);
                        putchar('\n');
                }
        }
}

void    west(int size)
{
        int     sp, i;

        sp = size;
        for (i = 1; i <= size + 1; i++, sp--)
        {
                if (i == 1)
                {
                        print(' ', sp);
                        printf("#\n");
                }
                else
                {
                        print(' ', sp);
                        print('#', i + size + 1);
                        putchar('\n');
                }
        }
        sp += 2;
        for (i = size; i > 0; i--, sp++)
        {
                if (i == 1)
                {
                        print(' ', sp);
                        printf("#\n");
                }
                else
                {
                        print(' ', sp);
                        print('#', i + size + 1);
                        putchar('\n');
                }
        }
}

void    print_arrow(char arrow, int size)
{
        if (size == 0)
                ;
        else if (arrow == 'N')
                north(size);
        else if (arrow == 'S')
                south(size);
        else if (arrow == 'E')
                east(size);
        else if (arrow == 'W')
                west(size);
}

int     main(void)
{
        int     size;
        char    arrow;

        scanf(" %c %d", &arrow, &size);
        print_arrow(arrow, size);
        return (0);
}
