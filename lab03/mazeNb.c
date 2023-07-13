#include <stdio.h>
#include <stdlib.h>

int	**create_mazeNb(int size)
{
	int	**mazeNb;

	mazeNb = (int **)malloc(sizeof(int *) * size);
	if (!mazeNb)
		mazeNb = NULL;
	for (int i = 0; i < size; i++)
	{
		mazeNb[i] = (int *)malloc(sizeof(int) * size);
		if (!mazeNb[i])
			mazeNb = NULL;
		for (int j = 0; j < size; j++)
			mazeNb[i][j] = 0;
	}
	return (mazeNb);
}

void	type_one(int **mazeNb, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 1; j <= size; j++)
			mazeNb[j - 1][i] += (i * size) + j;
}

void	type_two(int **mazeNb, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 1; j <= size; j++)
		{
			if (i % 2)
				mazeNb[size - j][i] += (i * size) + j;
			else
				mazeNb[j - 1][i] += (i * size) + j;
		}
}

void	type_three(int **mazeNb, int size)
{
	int	row, col, num;

	row = size - 1;
	col = 0;
	num = 1;
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i % 2)
				mazeNb[row--][col--] += num++;
			else
				mazeNb[row++][col++] += num++;
		}
		(i % 2) ? (col++) : (row--);
	}
	for (int i = size; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (i % 2)
				mazeNb[row--][col--] += num++;
			else
				mazeNb[row++][col++] += num++;
		}
		(i % 2) ? ((row++), (col += 2)) : ((row -= 2), (col--));
	}
}

void	type_four(int **mazeNb, int size)
{
	int	round;
	int	num;

	round = (size / 2) + (size % 2);
	num = 1;
	for (int i = 0; i < round; i++)
	{
		for (int j = 0; j < size - (2 * i); j++)
			if (!mazeNb[i + j][i])
				mazeNb[i + j][i] += num++;
		for (int j = 0; j < size - (2 * i); j++)
			if (!mazeNb[size - i - 1][i + j])
				mazeNb[size - i - 1][i + j] += num++;
		for (int j = 0; j < size - (2 * i); j++)
			if (!mazeNb[size - i - 1 - j][size - i - 1])
				mazeNb[size - i - 1 - j][size - i - 1] += num++;
		for (int j = 0; j < size - (2 * i); j++)
			if (!mazeNb[i][size - i - 1 - j])
				mazeNb[i][size - i - 1 - j] += num++;
	}
}

void	print_maze(int **mazeNb, int size, int type)
{
	switch (type)
	{
		case 1: type_one(mazeNb, size); break;
		case 2: type_two(mazeNb, size); break;
		case 3: type_three(mazeNb, size); break;
		case 4: type_four(mazeNb, size); break;
	}
	for (int i = 0; i < size; i++)
	{
		printf("%d", mazeNb[i][0]);
		for (int j = 1; j < size; j++)
			printf(" %d", mazeNb[i][j]);
		printf("\n");
		free(mazeNb[i]);
	}
}

int	main(void)
{
	int	size, type;
	int	**mazeNb;
	
	scanf("%d %d", &size, &type);
	mazeNb = create_mazeNb(size);
	print_maze(mazeNb, size, type);
	free(mazeNb);
	return (0);
}
