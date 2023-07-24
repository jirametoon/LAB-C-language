#include <stdio.h>

int	isPrime(int num)
{
	if (num == 2)
		return (1); // O(1)
	else if (!(num % 2) || num < 2)
		return (0); // O(1)
	for (int i = 1; (2*i + 1) * (2*i + 1) <= num; i++)
		if (!(num % (2*i + 1)))
			return (0); // O(sqrt(n))
	return (1);
}

int	main(void)
{
	int	num;

	scanf("%d", &num);
	printf("%d\n", isPrime(num));
	return (0);
}

/*
 *	1 + 1 + sqrt(n)/2
 *	O(1) + O(1) + O(sqrt(n)) = O(sqrt(n))
 */

// O(sqrt(n))
