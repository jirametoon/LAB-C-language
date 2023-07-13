#include <stdio.h>

void    print_month(int year, int month)
{
  switch (month)
  {
    case 1: printf("January %d\n", year); break;
    case 2: printf("February %d\n", year); break;
    case 3: printf("March %d\n", year); break;
    case 4: printf("April %d\n", year); break;
    case 5: printf("May %d\n", year); break;
    case 6: printf("June %d\n", year); break;
    case 7: printf("July %d\n", year); break;
    case 8: printf("August %d\n", year); break;
    case 9: printf("September %d\n", year); break;
    case 10: printf("October %d\n", year); break;
    case 11: printf("November %d\n", year); break;
    case 12: printf("December %d\n", year); break;
  }
}

int     day_of_the_month(int year, int month)
{
        if (month == 2)
        {
          if (year % 4)
            return (28);
          else
            return (29);
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
                return (30);
        else
               return (31);
}

int     cal_total_days(int year, int month)
{
        int     total_days, diff_year, i;

        diff_year = year - 1990;
        total_days = 0;
        for (i = 0; i < diff_year; i++)
          ((1990 + i) % 4) ? (total_days += 365) : (total_days += 366);
        for (i = 1; i < month; i++)
                total_days += day_of_the_month(year, i);
        return (total_days);
}

void    print_days(int year, int month)
{
        int     days, today, i;

        days = day_of_the_month(year, month);
        today = (cal_total_days(year, month) % 7) + 1;
        if (today != 7)
        {
                for (i = 0; i < today; i++)
                        printf("    ");
        }
        for (i = 1; i <= days; i++)
        {
          (i < 10) ? (printf("  %d", i)) : (printf(" %d", i));
          if (i != days)
            (!((i + today) % 7)) ? (putchar('\n')) : (putchar(' '));
        }
        putchar('\n');
}

int     main(void)
{
        int     year, month;

        printf("Enter year: ");
        scanf("%d", &year);
        printf("Enter month: ");
        scanf("%d", &month);
        printf("====================\n");
        print_month(year, month);
        printf("Sun Mon Tue Wed Thu Fri Sat\n");
        print_days(year, month);
        return (0);
}
