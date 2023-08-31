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

queue_t	*front = NULL;
queue_t	*rear = NULL;

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

tree_t	*last_child(tree_t *t)
{
	while (t -> first_child)
		t = t -> first_child;
	return (t);
}

tree_t	*last_sibling(tree_t *t)
{
	while (t -> next_sibling)
		t = t -> next_sibling;
	return (t);
}

tree_t	*attach(tree_t *t, int parent, int child)
{
	tree_t	*pos, *tmp;

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
	tmp = malloc(sizeof(tree_t));
	if (!tmp)
		return (t);
	tmp -> value = child;
	tmp -> next_sibling = NULL;
	tmp -> first_child = NULL;
	if (!pos -> first_child)
		pos -> first_child = tmp;
	else
	{
		pos = pos -> first_child;
		while (pos -> next_sibling)
			pos = pos -> next_sibling;
		pos -> next_sibling = tmp;
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

	while (search(t, node))
	{
		if (t -> value == node)
		{
			printf("%d", first -> value);
			while (first -> next_sibling)
			{
				first = first -> next_sibling;
				printf(" %d", first -> value);
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

int	main(void)
{
	tree_t	*t = NULL;		
	int		n, i, command;
	int		parent, child, node/*, start, end*/;

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
			//case 9: scanf("%d %d", &start, &end); print_path(t, start, end); break;
			//case 10: scanf("%d %d", &start, &end); printf("%d\n", path_length(t, start, end)); break;
			//case 11: scanf("%d", &node); ancestor(t, node); break;
			//case 12: scanf("%d", &node); descendant(t, node); break;
			//case 13: bfs(t); break;
			//case 14: dfs(t); break;
			//case 15: printree(t); break;
		}
	}
	return 0;
}
