#include <stdio.h>
#include <stdlib.h>

void	findStats(int n, int *nums, double *avg, int *maxi, int *mini)
{
	double	sum;

	sum = 0;
	*maxi = -999;
	*mini = 999;
	for (int i = 0; i < n; i++)
	{
		sum += *(nums + i);
		if (*maxi < *(nums + i))
			*maxi = *(nums + i);
		if (*mini > *(nums + i))
			*mini = *(nums + i);
	}
	*avg = sum / n;
}

int	main() {
	int	n, maxi, mini;
	double	avg;
	int	*nums;

	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) *n);
	for (int i=0; i<n; i++)
		scanf("%d", nums+i);
	findStats(n, nums, &avg, &maxi, &mini);
	printf("%.2f %d %d\n", avg, maxi, mini);
	return 0;
}
