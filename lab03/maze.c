#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define	FALSE 0

int	traverseMaze(char **maze, int size, int row, int col);

char	**create_maze(int size)
{
	char	**maze;
	char	c;
	int	j;

	maze = (char **)malloc(sizeof(char *) * size) ;
	if (!maze)
		return (NULL);
	for (int i = 0; i < size; i++)
	{
		maze[i] = (char *)malloc(sizeof(char) * (size + 1));
		if (!maze[i])
			return (NULL);
		j = 0;
		while ((c = getchar()) != '\n')
			maze[i][j++] = c;
		maze[i][size] = 0;
	}
	return (maze);
}

int	find_row_char(char **maze, int size, char c)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (maze[i][j] == c)
				return (i);
	return (-1);
}

int	find_col_char(char **maze, int size, char c)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (maze[i][j] == c)
				return (j);
	return (-1);
}

int	is_can_walk(char **maze, int size, int row, int col)
{
	if (row < 0 || col < 0 || row == size || col == size)
	       return (FALSE);
	if (maze[row][col] == ' ')
	{
		maze[row][col] = '.';
		return (TRUE);
	}
	else if (maze[row][col] == 'G')
		return (traverseMaze(maze, size, row, col));
	return (FALSE);
}

int	is_finish(char **maze, int row, int col)
{
	if (maze[row][col] == 'G')
		return (TRUE);
	return (FALSE);
}

int	traverseMaze(char **maze, int size, int row, int col)
{
	while (!is_finish(maze, row, col))
	{
		if (is_can_walk(maze, size, row, col + 1))
			if (traverseMaze(maze, size, row, col + 1))
				return (TRUE);
		if (is_can_walk(maze, size, row - 1, col))
			if (traverseMaze(maze, size, row - 1, col))
				return (TRUE);
		if (is_can_walk(maze, size, row, col - 1))
			if (traverseMaze(maze, size, row, col - 1))
				return (TRUE);
		if (is_can_walk(maze, size, row + 1, col))
			if (traverseMaze(maze, size, row + 1, col))
				return (TRUE);
		maze[row][col] = ' ';
		if (maze[row][col] == ' ')
			return (FALSE);
	}
	return (TRUE);
}

void	print_maze(char **maze, int size)
{
	for (int i = 0; i < size; i++)
		printf("%s\n", maze[i]);
}

int	main(void)
{
	char	**maze;
	int	size;

	scanf("%d\n", &size);
	maze = create_maze(size);
	//printf("==========================\n");
	if (find_row_char(maze, size, 'S') < 0 || find_col_char(maze, size, 'S') < 0)
		printf("There is no 'S' position.\n");
	else if (find_row_char(maze, size, 'G') < 0 || find_col_char(maze, size, 'G') < 0)
		printf("There is no 'G' position.\n");
	else if (traverseMaze(maze, size, find_row_char(maze, size, 'S'), find_col_char(maze, size, 'S')))
	{
		print_maze(maze, size);
		//printf("There is the way to walk from S(%d, %d) to G(%d, %d) (^-^)\n", \
			find_row_char(maze, size, 'S'), find_col_char(maze, size, 'S'), \
			find_row_char(maze, size, 'G'), find_col_char(maze, size, 'G'));
	}
	else
		printf("There is no path to walk to 'G' position (;-;)\n");
	for (int i = 0; i < size; i++)
		free(maze[i]);
	free(maze);
	return (0);
}
