#include <stdio.h>
#include <stdlib.h>

typedef struct	arr
{
	int			*data;
	int			last_index;
}arr_t;

arr_t	*createArray(int n)
{
	arr_t	*new_arr;

	new_arr = calloc(sizeof(arr_t), 1);
	if (!new_arr)
		return (NULL);
	new_arr -> data = calloc(sizeof(int), n);
	if (!new_arr -> data)
		return (NULL);
	return (new_arr);
}

void	insert(arr_t **arr, int m)
{
	if (!arr)
		return ;
	if (!*arr)
		return ;
	(*arr) -> data[(*arr) -> last_index] = m;
	(*arr) -> last_index++;
}

void	print(arr_t *arr)
{
	if (!arr)
		return ;
	printf("%d", arr -> data[0]);
	for (int i = 1; i < arr -> last_index; i++)
		printf(" %d", arr -> data[i]);
	printf("\n");
}

void	swap(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void	insertion_sort(arr_t **arr)
{
	if (!arr)
		return ;
	if (!*arr)
		return ;
	for (int i = 1; i < (*arr) -> last_index; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((*arr) -> data[j] >= (*arr) -> data[i])
				swap(&(*arr) -> data[j], &(*arr) -> data[i]);
		}
		print(*arr);
	}
}

int	main(void)
{
	int		n, m;
	arr_t	*arr = NULL;

	scanf("%d\n", &n);
	arr = createArray(n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &m);
		insert(&arr, m);
	}
	insertion_sort(&arr);
	return (0);
}
