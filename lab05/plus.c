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
	int	*res, *min, *max;
	int	size_max, size_min, n;

	if (num -> size_x < num -> size_y)
	{
		size_max = num -> size_y;
		size_min = num -> size_x;
		max = num -> y;
		min = num -> x;
	}
	else
	{
		size_max = num -> size_x;
		size_min = num -> size_y;
		max = num -> x; 
		min = num -> y;
	}
	res = (int *)malloc(sizeof(int) * size_max);
	n = 0;
	for (int i = 1; i <= size_min; i++)
	{
		res[i - 1] = (min[size_min - i] + max[size_max - i] + n) % 10;
		n = (min[size_min - i] + max[size_max - i] + n) / 10;
	}
	for (int i = size_min + 1; i <= size_max; i++)
	{
		res[i - 1] = (max[size_max - i] + n) % 10;
		n = (max[size_max - i] + n) / 10;
	}
	if (n)
	{
		res = (int *)realloc(res, sizeof(int) * (size_max + 1));
		res[size_max] = n;
		num -> size_res = size_max + 1;
	}
	else
		num -> size_res = size_max;
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
