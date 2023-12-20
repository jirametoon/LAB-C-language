#include <stdio.h>
#include <stdlib.h>

typedef struct	tree
{
	int			value;
	int			level;
	struct tree	*next_sibling;
	struct tree *first_child;
}tree_t;

typedef struct		stack
{
	int 			value;
	struct stack 	*next;
}s_stack_t;

typedef struct 		queue
{
	tree_t			*tree_node;
	struct queue	*next;
}queue_t;

queue_t	*enqueue(queue_t **q, tree_t *t)
{
	queue_t	*node = malloc(sizeof(queue_t));

	node->tree_node = t;
	node->next = NULL;
	if (!*q)
		return (node);
	else
	{
		queue_t	*tmp = *q;
		while(tmp -> next)
			tmp = tmp -> next;
		tmp -> next = node;
	}
	return (*q);
}

void	dequeue(queue_t **q)
{
	queue_t	*tmp = *q;

	printf("%d ",	(*q) -> tree_node -> value);
	*q = (*q) -> next;
	free(tmp);
}

queue_t	*createQueue(tree_t *t)
{
	queue_t	*q = malloc(sizeof(queue_t));

	q -> tree_node = t;
	q -> next = NULL;
	return (q);
}

s_stack_t	*push(s_stack_t **s, int value)
{
	s_stack_t *node = malloc(sizeof(s_stack_t));

	node -> value = value;
	node -> next = *s;
	return (node);
}

tree_t	*createTree(int value)
{
	tree_t	*t = malloc(sizeof(tree_t));

	t -> value = value;
	t -> level = 0;
	t -> next_sibling = NULL;
	t -> first_child = NULL;
	return (t);
}

tree_t	*find_node(tree_t *t, int value)
{
	tree_t	*pos;

	if (!t)
		return (t);
	if(t -> value == value)
		return (t);
	pos = find_node(t -> first_child, value);
	if(!pos)
		return (pos);
	return (find_node(t -> next_sibling, value));
}

tree_t	*find_parent(tree_t *t, tree_t *parent, int value)
{
	tree_t *pos;

	if(!t)
		return (NULL);
	if (t -> value == value)
		return (parent);
	pos = find_parent(t -> first_child, t, value);
	if(!pos)
		return (pos);
	return (find_parent(t -> next_sibling, parent, value));
}

int	search(tree_t *t, int value)
{
	return (find_node(t, value) != NULL);
}

tree_t	*findPath(tree_t *t, s_stack_t **path, int value)
{
	tree_t	*pos;

	if (!t)
		return (t);
	if (t -> value == value)
	{
		*path = push(path, value);
		return (t);
	}
	pos = findPath(t -> first_child, path, value);
	if (pos)
	{
		*path = push(path, t -> value);
		return (pos);
	}
	return (findPath(t -> next_sibling, path, value));
}

int	depth(tree_t *t, int node)
{
	int		count = 0;
	s_stack_t	*first_pos = NULL;
	s_stack_t	*tmp = NULL;
	tree_t		*end_pos = findPath(t, &first_pos, node);
	
	while (first_pos)
	{
		count++;
		tmp = first_pos -> next;
		free(first_pos);
		first_pos = tmp;
	}
	return (count);
}

tree_t *attach(tree_t *t,int parent, int child)
{
	tree_t	*node = createTree(child);
	if (parent == -1)
		return (node);
	tree_t *pos = find_node(t, parent);
	node -> level = depth(t, parent) + 1;
	if (!pos -> first_child)
		pos -> first_child = node;
	else
	{
		pos = pos -> first_child;
		while (pos -> next_sibling)
			pos = pos -> next_sibling;
		pos -> next_sibling = node;
	}	
	return (t);
}

int	degree(tree_t *t, int node)
{
	int	count = 0;
	tree_t	*pos = find_node(t, node) -> first_child;

	while (pos)
	{
		count++;
		pos = pos -> next_sibling;
	}
	return (count);
}

int	is_root(tree_t *t, int node)
{
	tree_t	*check = find_node(t, node);
	
	if (!check)
		return (0);
	if (!check -> level)
		return (1);
	return (0);
}

int	is_leaf(tree_t *t, int node)
{
	tree_t	*pos = find_node(t, node); 
	if (!pos)
		return (0);
	if (!pos -> first_child)
		return (1);
	return (0);
}

void	siblings(tree_t *t, int node)
{
	tree_t	*pos = find_parent(t, NULL, node);
	if (!pos)
		pos = pos -> first_child;
	while (pos)
	{
		if(pos->value != node)
			printf("%d ", pos->value);
		pos = pos->next_sibling;
	}
	printf("\n");
}


void	print_path(tree_t *t, int start, int end)
{
	s_stack_t	*path = NULL;
	s_stack_t	*tmp = NULL;
	tree_t		*endPos = findPath(find_node(t, start), &path, end);
	while (path)
	{
		printf("%d ", path -> value);
		tmp = path -> next;
		free(path);
		path = tmp;
	}
	printf("\n");
}

int	path_length(tree_t *t, int start, int end)
{
	int		count = 0;
	s_stack_t	*path = NULL;
	tree_t		*endPos = findPath(find_node(t, start), &path, end);
	s_stack_t	*tmp = NULL;
	
	while (path)
	{
		count++;
		tmp = path -> next;
		free(path);
		path = tmp;
	}
	return (count);
}

void	ancestor(tree_t *t, int node)
{
	s_stack_t	*path = NULL;
	s_stack_t	*tmp = NULL;
	tree_t		*endPos = findPath(t, &path, node);
	
	while (path)
	{
		printf("%d ", path -> value);
		tmp = path -> next;
		free(path);
		path = tmp;
	}
	printf("\n");
}

void	destroy(tree_t *t)
{
	if(t)
	{
		destroy(t -> first_child);
		destroy(t -> next_sibling);
		free(t);
	}
}

tree_t	*detach(tree_t *t, int node)
{
	tree_t	*dNode = find_node(t, node);
	tree_t *pdNode = find_parent(t, NULL, node);
	tree_t *tmp = NULL;
	
	if(pdNode)
	{
		if (pdNode -> first_child && pdNode -> first_child -> value != node)
		{
			pdNode = pdNode -> first_child;
			while (pdNode != dNode)
			{
				tmp = pdNode;
				pdNode = pdNode -> next_sibling;
			}
			tmp -> next_sibling = pdNode -> next_sibling;
		}
		else
			pdNode -> first_child = dNode -> next_sibling;
		dNode -> next_sibling = NULL;
		destroy(dNode);
	}
	else
	{
		destroy(dNode);
		t = NULL;
	}
	return (t);
}

void	dfs(tree_t *t)
{
	if (t)
	{
		printf("%d ",t -> value);
		dfs(t -> first_child);
		dfs(t -> next_sibling);
		if (is_root(t,t -> value))
			printf("\n");
	}
}

void bfs(tree_t *t)
{
	tree_t	*check, *tmp;
	queue_t	*qBfs;
	
	check = t;
	if (check)
	{
		qBfs = createQueue(check);
		while (qBfs)
		{
			if (!check -> next_sibling)
				if (check -> first_child)
				{
					qBfs = enqueue(&qBfs, check -> first_child);
					tmp = check -> first_child;
					while (tmp)
					{
						tmp = tmp -> next_sibling;
						if(tmp)
							qBfs = enqueue(&qBfs, tmp);
					}
				}
			dequeue(&qBfs);
		}
	}
	else
	{
		if (check -> first_child)
		{
			qBfs = enqueue(&qBfs, check -> first_child);
			tmp = check -> first_child;
			while (tmp)
			{
				tmp = tmp -> next_sibling;
				if (tmp)
					qBfs = enqueue(&qBfs,tmp);
			}
		}
		dequeue(&qBfs);
	}
	if(qBfs)
		check = qBfs -> tree_node;
    printf("\n");
}

void descendant(tree_t *t, int node)
{
	tree_t	*pos = find_node(t, node);
	bfs(pos);
}

void	print_tree(tree_t *t)
{
	if (t)
	{
		for (int i = 0; i < t -> level; i++)
			printf("    ");
	printf("%d\n",t->value);
	print_tree(t->first_child);
	print_tree(t->next_sibling);
	}
}

int	main(void)
{
	tree_t	*t = NULL;
	int	n, i, command;
	int	parent, child, node, start, end;
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		scanf("%d", &command);
		switch(command)
		{
			case 1: scanf("%d %d", &parent, &child); t = attach(t, parent, child); break;
			case 2: scanf("%d", &node); t = detach(t, node); break;
			case 3: scanf("%d", &node); printf("%d\n", search(t, node)); break;
			case 4: scanf("%d", &node); printf("%d\n", degree(t, node)); break;
			case 5: scanf("%d", &node); printf("%d\n", is_root(t, node)); break;
			case 6: scanf("%d", &node); printf("%d\n", is_leaf(t, node)); break;
			case 7: scanf("%d", &node); siblings(t, node); break;
			case 8: scanf("%d", &node); printf("%d\n", depth(t, node)); break;
			case 9: scanf("%d %d", &start, &end); print_path(t, start, end); break;
			case 10: scanf("%d %d", &start, &end); printf("%d\n",path_length(t, start, end)); break;
			case 11: scanf("%d", &node); ancestor(t, node); break;
			case 12: scanf("%d", &node); descendant(t, node); break;
			case 13: bfs(t); break;
			case 14: dfs(t); break;
			case 15: print_tree(t); break;
		}
	}
	return (0);
}

// credit:	pichpeach
