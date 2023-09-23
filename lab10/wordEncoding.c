#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef	struct	tree
{
	int 		frequency;
	char		*text;
	struct tree *left;
	struct tree *right;
}				tree_t;

typedef struct	heap
{
	tree_t		**data;
	int			last_index;
}				heap_t;

void	show_tree_2(tree_t *tree, int depth, char pre)
{
	int	i;
	
	if (!tree)
		return ;
	for (i = 0; i < depth; i++)
		printf("    ");
	printf("%c%d -> %s\n", pre, tree -> frequency, tree -> text);
	show_tree_2(tree -> left, depth + 1, 'L');
	show_tree_2(tree -> right, depth + 1, 'R');
}

void	show_tree(tree_t *tree)
{
	show_tree_2(tree, 0, 'r');
}

void	show(heap_t *min_heap)
{
	for (int j = 0; j < min_heap -> last_index; j++)
	{
		if (min_heap -> data[j])
			printf("tree[%d]:\n", j);
		show_tree(min_heap -> data[j]);
	}
	printf("========================================\n");
}

heap_t	*init_heap(int m)
{
	heap_t	*heap;

	heap = malloc(sizeof(heap_t));
	if (!heap)
		return (NULL);
	heap -> data = calloc(sizeof(tree_t *), m);
	if (!heap -> data)
		return (NULL);
	heap -> last_index = 0;
	return (heap);
}

tree_t	*createTree(const char *str, int freq)
{
	tree_t *tree = malloc(sizeof(tree_t));
	if (!tree)
		return (NULL);
	tree -> frequency = freq;
	tree -> text = strdup(str);
	tree -> left = NULL;
	tree -> right = NULL;
	return (tree);
}

void	swap(tree_t **tree1, tree_t **tree2)
{
	tree_t	*tmp;

	tmp = *tree1;
	*tree1 = *tree2;
	*tree2 = tmp;
}

void	make_tree_complete_leaf(heap_t *min_heap, int index)
{
	int	parent;

	if (min_heap && index && min_heap -> data[index])
	{
		if (index % 2)
			parent = (index - 1) / 2;
		else
			parent = (index - 2) / 2;
		if (min_heap -> data[index] -> frequency < min_heap -> data[parent] -> frequency)
		{
			swap(&min_heap -> data[index], &min_heap -> data[parent]);
			//show(min_heap);
			make_tree_complete_leaf(min_heap, parent);
		}
	}	
}

int	min_tree(heap_t *min_heap, int left, int right)
{	
	if (left > min_heap -> last_index && right > min_heap -> last_index)
		return (-1);
	if (min_heap -> data[left] && min_heap -> data[right])
	{
		if (min_heap -> data[left] -> frequency <= min_heap -> data[right] -> frequency)
			return (left);
		else
			return (right);
	}
	else if (min_heap -> data[left])
		return (left);
	else if (min_heap -> data[right])
		return (right);
	return (-1);
}

void	make_tree_complete_root(heap_t *min_heap, int index)
{
	int		min_t;

	if (min_heap && min_heap -> data[index] \
		&& (min_heap -> data[2 * index + 1] || min_heap -> data[2 * index + 2]))
	{
		min_t = min_tree(min_heap, 2 * index + 1, 2 * index + 2);
		if (min_t >= 0)
		{
			if (min_heap -> data[index] -> frequency > min_heap -> data[min_t] -> frequency)
			{
				swap(&min_heap -> data[index], &min_heap -> data[min_t]);
				//show(min_heap);
				make_tree_complete_root(min_heap, min_t);
			}
		}
	}	
}

void	insert_str(heap_t *min_heap, const char *str, int freq)
{
	if (min_heap)
	{
		min_heap -> data[min_heap -> last_index] = createTree(str, freq);
		make_tree_complete_leaf(min_heap, min_heap -> last_index);
		min_heap -> last_index++;
	}
}

tree_t	*delete_min(heap_t *min_heap)
{
	tree_t	*tree;

	if (!min_heap || !min_heap -> data[0])
		return (NULL);
	tree = min_heap -> data[0];
	min_heap -> last_index--;
	swap(&min_heap -> data[0], &min_heap -> data[min_heap -> last_index]);
	min_heap -> data[min_heap -> last_index] = NULL;
	make_tree_complete_root(min_heap, 0);
	return (tree);
}

tree_t	*createNewTree(tree_t *tree1, tree_t *tree2)
{
	tree_t *tree = malloc(sizeof(tree_t));
	if (!tree)
		return (NULL);
	tree -> frequency = tree1 -> frequency + tree2 -> frequency;
	tree -> text = NULL;
	tree -> left = tree1;
	tree -> right = tree2;
	return (tree);
}

void	insert_tree(heap_t *min_heap, tree_t *tree1, tree_t *tree2)
{
	if (min_heap && tree1 && tree2)
	{
		min_heap -> data[min_heap -> last_index] = createNewTree(tree1, tree2);
		make_tree_complete_leaf(min_heap, min_heap -> last_index);
		min_heap -> last_index++;
	}
}

int	searchTree(tree_t *tree, const char *text)
{
	if (!tree)
		return (0);
	if (tree -> text)
		if (!strcmp(tree -> text, text))
			return (1);
	return (searchTree(tree -> left, text) || searchTree(tree -> right, text));
}

void	print_code(tree_t *root, const char *text)
{
	if (searchTree(root, text))
	{
		if (searchTree(root -> left, text))
		{
			printf("0");
			print_code(root -> left, text);
		}
		else if (searchTree(root -> right, text))
		{
			printf("1");
			print_code(root -> right, text);
		}
	}
}

void	print_tree(tree_t *root, tree_t *tree)
{
	if (root && tree)
	{
		if (tree -> text)
		{
			printf("%s: ", tree -> text);
			print_code(root, tree -> text);
			printf("\n");
		}
		print_tree(root, tree -> left);
		print_tree(root, tree -> right);
	}
}

void	free_tree(tree_t *tree)
{
    if (tree)
	{
        free_tree(tree -> left);
        free_tree(tree -> right);
        free(tree -> text);
        free(tree);
	}
}

int	main(void)
{
	heap_t	*min_heap = NULL;
	tree_t	*tree1, *tree2;
	int		m, freq;
	char	str[15];

	scanf("%d", &m);
	min_heap = init_heap(m);
	for (int i = 0; i < m; i++)
	{
		scanf("%s %d", str, &freq);
		insert_str(min_heap, str, freq);
	}

	//printf("tree:\n");
	//show(min_heap);

	while (min_heap -> last_index > 1)
	{
		tree1 = delete_min(min_heap);
		//printf("delete 1:\n");
		//show(min_heap);

		tree2 = delete_min(min_heap);
		//printf("delete 2:\n");
		//show(min_heap);

		insert_tree(min_heap, tree1, tree2);
		//printf("insert:\n");
		//show(min_heap);
	}
	//show(min_heap);
	//show_tree(min_heap -> data[0]);
	
	print_tree(min_heap -> data[0], min_heap -> data[0]);
	free_tree(min_heap -> data[0]);
	free(min_heap);
	return (0);
}