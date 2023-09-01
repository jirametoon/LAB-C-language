#include <stdio.h>
#include <stdlib.h>

// You can define your own (one or more)
// structures here. However, we eventually
// need the data type "tree_t".
// For example:
// typedef struct node {
// ...
// } node_t;
// typedef node_t tree_t;
// Write your code here
// ...

typedef	struct	node_tree
{
	int					value;
	struct	node_tree	*next_sibling;
	struct	node_tree	*first_child;
}node_tree_t;

typedef struct	node
{
		int			value;
		struct node	*next;
}node_t;

typedef node_tree_t	tree_t;	
typedef	node_t		s_stack_t;
typedef node_t		queue_t;

void	enqueue(queue_t **front, queue_t **rear, int value)
{
	queue_t	*node;

	node = malloc(sizeof(queue_t));
	if (node)
	{
		node -> value = value;
		node -> next = NULL;
		if (!*front)
		{
			*front = node;
			*rear = node;
		}
		else
		{
			(*rear) -> next = node;
			*rear = (*rear) -> next;
		}
	}
}

tree_t	dequeue(queue_t	*front)
{
	queue_t	*node;

	node = *front;
	if (node)
	{
		*front = (*front) -> next;
		free(node);
	}
}

tree_t	*find_node(tree_t *t, int node)
{
	tree_t	*pos;

	if (!t)
		return (t);
	if (t -> value == node)
		return (t);
	pos = find_node(t -> first_child, node);
	if (!pos)
		return (find_node(t -> next_sibling, node));
	return (pos);
}


tree_t	*attach(tree_t *t, int parent, int child)
{
	tree_t	*pos, *node;

	if (parent != -1 && !t)
		return (NULL);
	if (parent == -1 && !t)
	{
		pos = malloc(sizeof(tree_t));
		if (!pos)
				return (NULL);
		pos -> value = child;
		pos -> next_sibling = NULL;
		pos -> first_child = NULL;
		return (pos);
	}
	pos = find_node(t, parent);
	if (!pos)
		return (t);
	node = malloc(sizeof(tree_t));
	if (!tmp)
		return (t);
	node -> value = child;
	node -> next_sibling = NULL;
	node -> first_child = NULL;
	if (!pos -> first_child)
		pos -> first_child = tmp;
	else
	{
		pos = pos -> first_child;
		while (pos -> next_sibling)
			pos = pos -> next_sibling;
		pos -> next_sibling = node;
	}
	return (t);
}

/*
tree_t	*detach(tree_t *t, int node)
{

}
*/

int	search(tree_t *t, int node)
{
	return (find_node(t, node) != NULL);
}

int	degree(tree_t *t, int node)
{
	int	count;

	t = find_node(t, node);
	if (!t)
		return (0);
	t = t -> first_child;
	count = 0;
	while (t)
	{
		count++;
		t = t -> next_sibling;
	}
	return (count);
}

int	is_root(tree_t *t, int node)
{
	if (!t)
		return (0);
	if (t -> value == node)
		return (1);
	return (0);
}

int	is_leaf(tree_t *t, int node)
{
	t = find_node(t, node);
	if (!t)
		return (0);
	if (!t -> first_child)
		return (1);
	return (0);
}

void	siblings(tree_t *t, int node)
{
	tree_t	*first = t;
	int		i = 1;

	while (search(t, node))
	{
		if (t -> value == node)
		{
			while (first)
			{
				if (first -> value != node)
				{
					if (i)
					{
						printf("%d", first -> value);
						i = 0;
					}
					else
						printf(" %d", first -> value);
				}
				first = first -> next_sibling;
			}
			printf("\n");
			t = NULL;
		}
		else if (search(t -> first_child, node))
		{
			t = t -> first_child;
			first = t;
		}
		else
			t = t -> next_sibling;
	}
}

/*
int	depth(tree_t *t, int node)
{

}	
*/

void	print_path(tree_t *t, int start, int end)
{
	tree_t	*tmp = find_node(t, start);

	t = tmp;
	if (tmp && search(tmp, end))
	{
		while (search(t, end))
		{
			if (tmp -> value == end)
			{
				printf("%d\n", end);
				t = NULL;
			}
			else if (search(tmp -> first_child, end))
			{
				printf("%d ", tmp -> value);
				tmp = tmp -> first_child;
			}
			else
				tmp = tmp -> next_sibling;
		}
	}
}

int	path_length(tree_t *t, int start, int end)
{
	tree_t	*tmp = find_node(t, start);
	int		count = 1;

	if (!(tmp && search(tmp, end)))
		return (0);
	while (search(t, end))
	{
		if (tmp -> value == end)
			t = NULL;
		else if (search(tmp -> first_child, end))
		{
			count++;
			tmp = tmp -> first_child;
		}
		else
			tmp = tmp -> next_sibling;
	}
	return (count);
}

void	ancestor(tree_t *t, int node)
{
	if (t && search(t, node))
	{
		while (search(t, node))
		{
			if (t -> value == node)
			{
				printf("%d\n", node);
				t = NULL;
			}
			else if (search(t -> first_child, node))
			{
				printf("%d ", t -> value);
				t = t -> first_child;
			}
			else
				t = t -> next_sibling;
		}
	}
}

void	bfs(t)
{
}

int	main(void)
{
	tree_t	*t = NULL;		
	int		n, i, command;
	int		parent, child, node, start, end;

	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		scanf("%d", &command);
		switch(command)
		{
			case 1:	scanf("%d %d", &parent, &child); t = attach(t, parent, child); break;
			//case 2: scanf("%d", &node); t = detach(t, node); break;
			case 3: scanf("%d", &node); printf("%d\n", search(t, node)); break;
			case 4: scanf("%d", &node); printf("%d\n", degree(t, node)); break;
			case 5: scanf("%d", &node); printf("%d\n", is_root(t, node)); break;
			case 6: scanf("%d", &node); printf("%d\n", is_leaf(t, node)); break;
			case 7: scanf("%d", &node); siblings(t, node); break;
			//case 8: scanf("%d", &node); printf("%d\n", depth(t, node)); break;
			case 9: scanf("%d %d", &start, &end); print_path(t, start, end); break;
			case 10: scanf("%d %d", &start, &end); printf("%d\n", path_length(t, start, end)); break;
			case 11: scanf("%d", &node); ancestor(t, node); break;
			//case 12: scanf("%d", &node); descendant(t, node); break;
			//case 13: bfs(t); break;
			//case 14: dfs(t); break;
			//case 15: printree(t); break;
		}
	}
	return 0;
}
