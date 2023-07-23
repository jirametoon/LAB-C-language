#include <stdio.h>
#include <math.h>

int	last_num(int row, int col)
{
	int	num;

	if (row <= col)
		for (float i = 0.0; pow(2.0, i) <= row; i++)
			num = pow(2.0, i); // O(lgn)
	else
		for (float i = 0.0; pow(2.0, i) <= col; i++)
			num = pow(2.0, i); // O(lgn)
	return (num);
}


int	estatePlanner(int row, int col)
{
	int	num;

	num = last_num(row, col);
	if (row == 0 || col == 0)
		return (0);
	else if (row != num && col != num)
		return (estatePlanner(row - num, col) + estatePlanner(col - num, num) + 1);
	else if (row != num)
		return (estatePlanner(row - num, col) + 1);
	else if (col != num)
		return (estatePlanner(row, col - num) + 1);
	else
	{
		if (row < col)
			return (col / num);
		else
			return (row / num);
	}
}

int	main(void)
{
	int	row, col;

	scanf("%d %d", &row, &col);
	printf("%d\n", estatePlanner(row, col));
	return (0);
}

/* 
 * T(min(row, col))	-> O(1) + O(lg(min(row, col)))								(row == 0 || col == 0)
 * 			-> O(lg(min(row, col))) + T(min(row - num, col)) + T(min(col - num, num)) + O(1)	(row != num && col != num)
 * 			-> O(lg(min(row, col))) + T(min(row - num), col) + O(1)					(row != num)
 * 			-> O(lg(min(row, col))) + T(min(row, col - num)) + O(1)					(col != num)
 * 			-> O(lg(min(row, col))) + O(1)								otherwise
 */
