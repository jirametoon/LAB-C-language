#include <stdio.h>

int	last_num(int num)
{
	int	lnum;

	lnum = 0;
	for (int i = 1; i <= num; i *= 2)
		lnum = i;
	return (lnum);
}

int	estatePlanner(int row, int col)
{
	int	lnum;

	if (row > col)
		return (estatePlanner(col, row));
	lnum = last_num(row);
	if (!row)
		return (0);
	else if (row == lnum && !(col % lnum))
		return (col / lnum);
	else
		return (estatePlanner(row - lnum, col) + estatePlanner(lnum, col - lnum) + 1);
}

int	main(void)
{
	int	row, col;

	scanf("%d %d", &row, &col);
	printf("%d\n", estatePlanner(row, col));
	return (0);
}

/*
 * T(row, col) = T(row - lnum, col) + T(lnum, col - lnum) + 1
 * lnum = O(log(min(row, col)))
 * T(row, col) = O(log(row)) * O(log(col))
 */

// O(log(n))
