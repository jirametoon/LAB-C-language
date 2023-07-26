#include <stdio.h>
#include <stdlib.h>

typedef struct	num
{
	int	*x;
	int	*y;
	int	*res;
	int	size_x;
	int	size_y;
	int	size_res;
} num_t;

int	*getNUM(int *size)
{
	int	*num;
	char	c;

	num = (int *)malloc(sizeof(int));
	while ((c = getchar()) != '\n')
	{
		num = (int *)realloc(num, sizeof(int) * (*size + 1));
		if (!num)
			return (0);
		num[*size] = c - '0';
		(*size)++;
	}
	return (num);
}

int	*plus(num_t *num)
{
	int	*res;
	int	max, min, n;

	if (num -> size_x < num -> size_y)
	{
		max = num -> size_y;
		min = num -> size_x;
	}
	else
	{
		max = num -> size_x;
		min = num -> size_y;
	}
	res = (int *)malloc(sizeof(int) * max);
	n = 0;
	for (int i = 1; i <= min; i++)
	{
		res[i - 1] = (num -> x[(num -> size_x) - i] + num -> y[(num -> size_y) - i] + n) % 10;
		n = (num -> x[(num -> size_x) - i] + num -> y[(num -> size_y) - i] + n) / 10;
	}
	for (int i = min + 1; i <= max; i++)
	{
		if (num -> size_x < num -> size_y)
		{
			res[i - 1] = (num -> y[(num -> size_y) - i] + n) % 10;
			n = (num -> y[(num -> size_y) - i] + n) / 10;
		}
		else
		{
			res[i - 1] = (num -> x[(num -> size_x) - i] + n) % 10;
			n = (num -> x[(num -> size_x) - i] + n) / 10;
		}
	}
	if (n)
	{
		res = (int *)realloc(res, sizeof(int) * (max + 1));
		res[max] = n;
		num -> size_res = max + 1;
	}
	else
		num -> size_res = max;
	return (res);
}

int	main(void)
{
	num_t	num;

	num.size_x = 0;
	num.size_y = 0;
	num.x = getNUM(&num.size_x);
	num.y = getNUM(&num.size_y);
	num.res = plus(&num);
	for (int i = 1; i <= num.size_res; i++)
		printf("%d", num.res[num.size_res - i]);
	printf("\n");
	free(num.x);
	free(num.y);
	free(num.res);
	return (0);
}
