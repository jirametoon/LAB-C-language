#include <stdio.h>
#include <stdlib.h>

void	count_num(int *Cnum, int *num, int round)
{
	for (int i = 0; i < 100; i++)
		Cnum[i] = 0;
	for (int i = 0; i < round; i++)
		Cnum[num[i] - 1]++;
}

int	find_max_num(int *Cnum)
{
	int	index;

	index = 0;
	for (int i = 0; i < 100; i++)
		if (Cnum[index] < Cnum[i])
			index = i;
	return (Cnum[index]);
}

void	print_num(int *Cnum, int max)
{
	int	i;

	for (i = 0; i < 100; i++)
		if (Cnum[i] == max)
		{
			printf("%d", i + 1);
			break ;
		}
	for (int j = i + 1; j < 100; j++)
		if (Cnum[j] == max)
			printf(" %d", j + 1);
	printf("\n");
}

int	main(void)
{
	int	round, max, Cnum[100];
	int	*num;

	scanf("%d", &round);
	num = (int *)malloc(sizeof(int) * round);
	if (!num)
	{
		num = NULL;
		return (1);
	}
	for (int i = 0; i < round; i++)
		scanf("%d", &num[i]);
	count_num(Cnum, num, round);
	max = find_max_num(Cnum);
	print_num(Cnum, max);
	free(num);
	return (0);
}
