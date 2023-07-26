#include <stdio.h>

typedef struct  datetime
{
        int     date;           // 1-31
        int     month;          // 1-12
        int     year;           // 1970++
        int     dayOfWeek;      // 0-6
        int     hour;           // 0-23
        int     minute;         // 0-59
        int     second;         // 0-59
} datetime_t;

void    printDayOrMonth(char c, int num)
{
        if (c == 'm')
                switch (num)
                {
                        case 1: printf("JAN "); break;
                        case 2: printf("FEB "); break;
                        case 3: printf("MAR "); break;
                        case 4: printf("APR "); break;
                        case 5: printf("MAY "); break;
                        case 6: printf("JUN "); break;
                        case 7: printf("JUL "); break;
                        case 8: printf("AUG "); break;
                        case 9: printf("SEP "); break;
                        case 10: printf("OCT "); break;
                        case 11: printf("NOV "); break;
                        case 12: printf("DEC "); break;
                }
        else if (c == 'd')
                switch (num)
                {
                        case 0: printf("Thu "); break;
                        case 1: printf("Fri "); break;
                        case 2: printf("Sat "); break;
                        case 3: printf("Sun "); break;
                        case 4: printf("Mon "); break;
                        case 5: printf("Tue "); break;
                        case 6: printf("Wed "); break;
                }
}

void    printTime(char c, int num)
{
        if (num < 10)
                printf("0%d", num);
        else
                printf("%d", num);
        if (c == 's')
                printf("\n");
        else
                printf(":");
}

int     dayOfMonth(int m, int y)
{
        if (m == 4 || m == 6 || m == 9 || m == 11)
                return (30);
        else if (m == 2)
        {
                if (y % 4)
                        return (28);
                else
                        return (29);
        }
        else
                return (31);
}

int     dayOfYear(int y)
{
        if (y % 4)
                return (365);
        else
                return (366);
}

datetime_t      createDate(int timestamp)
{
        datetime_t      inputDate;

        inputDate.second = timestamp % 60;
        timestamp /= 60;
        inputDate.minute = timestamp % 60;
        timestamp /= 60;
        inputDate.hour = timestamp % 24;
        timestamp /= 24;
        inputDate.dayOfWeek = timestamp % 7;
        inputDate.month = 1;
        inputDate.year = 1970;
        while (timestamp > dayOfMonth(inputDate.month, inputDate.year))
        {
                timestamp -= dayOfMonth(inputDate.month++, inputDate.year);
                if (inputDate.month > 12 && inputDate.year++)
                        inputDate.month = 1;
        }
        if (timestamp + 1 > dayOfMonth(inputDate.month, inputDate.year))
        {
                timestamp = 0;
                inputDate.month++;
        }
        inputDate.date = ++timestamp;
        return (inputDate);
}

void    printDate(datetime_t inputDate)
{
        printDayOrMonth('d', inputDate.dayOfWeek);
        printf("%d ", inputDate.date);
        printDayOrMonth('m', inputDate.month);
        printf("%d ", inputDate.year);
        printTime('h', inputDate.hour);
        printTime('m', inputDate.minute);
        printTime('s', inputDate.second);
}

int     main(void)
{
        datetime_t      inputDate;
        int             timestamp;

        scanf("%d", &timestamp);
        inputDate = createDate(timestamp);
        printDate(inputDate);
        return (0);
}
