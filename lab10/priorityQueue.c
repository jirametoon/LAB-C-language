#include <stdio.h>
#include <stdlib.h>

typedef struct	heap
{
	int			*data;
	int			last_index;
}				heap_t;
// Write your code here
// ...

void	swap(heap_t *max_heap, int index1, int index2)
{
	max_heap -> data[index1] += max_heap -> data[index2];
	max_heap -> data[index2] = max_heap -> data[index1] - max_heap -> data[index2];
	max_heap -> data[index1] -= max_heap -> data[index2];
}

void	make_tree_complete_leaf(heap_t *max_heap, int index)
{
	int	parent;

	if (max_heap && index)
	{
		if (index % 2)
			parent = (index - 1) / 2;
		else
			parent = (index - 2) / 2;
		if (max_heap -> data[index] > max_heap -> data[parent])
		{
			swap(max_heap, index, parent);
			make_tree_complete_leaf(max_heap, parent);
		}
	}	
}

void	make_tree_complete_root(heap_t *max_heap, int index)
{
	if (max_heap)
	{
		if (max_heap -> data[index] < max_heap -> data[2 * index + 1])
		{
			swap(max_heap, index, 2 * index + 1);
			make_tree_complete_leaf(max_heap, 2 * index + 1);
		}
		else if (max_heap -> data[index] < max_heap -> data[2 * index + 2])
		{
			swap(max_heap, index, 2 * index + 2);
			make_tree_complete_root(max_heap, 2 * index + 2);
		}
	}	
}

heap_t	*init_heap(int m)
{
	heap_t	*heap;

	heap = malloc(sizeof(heap_t));
	if (!heap)
		return (NULL);
	heap -> data = calloc(sizeof(int), m);
	if (!heap -> data)
		return (NULL);
	heap -> last_index = m;
	return (heap);
}

void	insert(heap_t *max_heap, int data)
{
	if (max_heap)
	{
		for (int index = 0; index < max_heap -> last_index; index++)
			if (!max_heap -> data[index] || index == max_heap -> last_index)
			{
				if (index != max_heap -> last_index)
				{
					max_heap -> data[index] = data;
					make_tree_complete_leaf(max_heap, index);
					break ;
				}
			}
	}
}

void	delete_max(heap_t *max_heap)
{
	if (max_heap)
	{
		for (int index = 0; index < max_heap -> last_index; index++)
			if (!max_heap -> data[index])
			{
				max_heap -> data[0] = 0;
				swap(max_heap, 0, index - 1);
				break ;
			}
		make_tree_complete_root(max_heap, 0);
	}
}

int	find_max(heap_t *max_heap)
{
	if (!max_heap -> data[0])
		return (-1);
	return (max_heap -> data[0]);
}

void	update_key(heap_t *max_heap, int old_key, int new_key)
{
	if (max_heap)
	{
		for (int index = 0; index < max_heap -> last_index; index++)
			if (old_key == max_heap -> data[index])
			{
				max_heap -> data[index] = new_key;
				make_tree_complete_leaf(max_heap, index);
				break ;
			}
	}
}

void	bfs(heap_t	*max_heap)
{
	if (max_heap)
	{
		if (max_heap -> data[0])
			printf("%d", max_heap -> data[0]);
		for (int i = 1; i < max_heap -> last_index; i++)
		{
			if (!max_heap -> data[i])
				break ;
			printf(" %d", max_heap -> data[i]);
		}
		printf("\n");
	}
}

int	main(void)
{
	heap_t	*max_heap = NULL;
	int		m, n, i;
	int		command, data;
	int		old_key, new_key;
	
	scanf("%d %d", &m, &n);
	max_heap = init_heap(m);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &command);
		switch (command)
		{
			case 1: scanf("%d", &data); insert(max_heap, data); break;
			case 2: delete_max(max_heap); break;
			case 3: printf("%d\n", find_max(max_heap)); break;
			case 4: scanf("%d %d", &old_key, &new_key); update_key(max_heap, old_key, new_key); break;
			case 5: bfs(max_heap); break;
		}
	}
	return (0);
}