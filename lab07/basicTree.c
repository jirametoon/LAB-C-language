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

typedef	struct	node
{
	int				value;
	struct	node	*next_sibling;
	struct	node	*first_child;
}node_t;

typedef node_t	tree_t;	

tree_t	*find(tree_t *t, int node)
{
		tree_t	*pos;

		if (!t)
				return (NULL);
		if (t -> value == node)
				return (t);
		pos = find(t -> first_child, node);
		if (!pos)
				return (find(t -> next_sibling, node));
		return (pos);
}

tree_t *last_sibling(tree_t *t)
{
	while (t -> next_sibling)
		t = t -> next_sibling;
	return (t);
}

tree_t *last_child(tree_t *t)
{
	while (t -> first_child)
		t = t -> first_child;
	return (t);
}

tree_t	*last_tree(tree_t *t)
{
		tree_t	*pos;

		pos = t;
		while (pos -> first_child)
				pos = pos -> first_child;
		while (pos -> next_sibling)
				pos = pos -> next_sibling;
		return (pos);
}

tree_t	*attach(tree_t *t, int parent, int child)
{
	tree_t	*pos, *tmp;
	
	pos = find(t, parent);
	if (!pos)
			return (t);
	pos = pos -> first_child;
	tmp = malloc(sizeof(tree_t));
	tmp -> value = child;
	tmp -> next_sibling = NULL;
	tmp -> first_child = NULL;
	while (pos -> next_sibling)
			pos = pos -> next_sibling;
	pos -> next_sibling = tmp;
	return (t);
}

tree_t	*detach(tree_t *t, int node)
{
		tree_t	*pos, *rm_t;

		pos = find(t, node);
		while (pos)
		{
				rm_t = last_tree(pos);
				rm_t = NULL;
				free(rm_t);
		}
		return (t);
}

int	search(tree_t *t, int node)
{
		tree_t *pos;

		pos = find(t, node);
		if (pos)
				return (1);
		return (0);
}

int	degree(tree_t *t, int node)
{
		tree_t	*pos;
		int		count;

		pos = find(t,  node) -> first_child;
		count = 0;
		while (pos)
		{
				pos = pos -> next_sibling;
				count++;
		}
		return (count);
}

int	is_root(tree_t *t, int node)
{
		return (t -> value == node);
}

int	is_leaf(tree_t *t, int node)
{
		tree_t	*pos;

		pos = find(t, node);
		return (!(pos -> first_child));
}

void	siblings(tree_t *t, int	node)
{
		tree_t	*pos, *tmp;

		tmp = t;
		while (tmp && tmp -> value != node)
		{
				pos = tmp;
				while (tmp && tmp -> value != node)
						tmp = tmp -> next_sibling;
				tmp = pos -> first_child;
		}
		if (tmp && pos)
		{
			printf("%d", pos -> value);
			pos = pos -> next_sibling;
		}
		while (tmp && pos)
		{
				printf(" %d", pos -> value);
				pos = pos -> next_sibling;
		}
}

int	depth(tree_t *t, int node)
{
		tree_t *pos;
		int		count;

		pos = find(t, node);
		count = -1;
		while (pos -> first_child)
		{
				count++;
				pos = pos -> first_child;
		}
		return (count);
}

void	print_path(tree_t *t, int start, int end)
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
						case 2: scanf("%d", &node); t = detach(t, node); break;
						case 3: scanf("%d", &node); printf("%d\n", search(t, node)); break;
						case 4: scanf("%d", &node); printf("%d\n", degree(t, node)); break;
						case 5: scanf("%d", &node); printf("%d\n", is_root(t, node)); break;
						case 6: scanf("%d", &node); printf("%d\n", is_leaf(t, node)); break;
						case 7: scanf("%d", &node); siblings(t, node); break;
						case 8: scanf("%d", &node); printf("%d\n", depth(t, node)); break;
						case 9: scanf("%d %d", &start, &end); print_path(t, start, end); break;
						case 10: scanf("%d %d", &start, &end); printf("%d\n", path_length(t, start, end)); break;
						case 11: scanf("%d", &node); ancestor(t, node); break;
						case 12: scanf("%d", &node); descendant(t, node); break;
						case 13: bfs(t); break;
						case 14: dfs(t); break;
						case 15: print_tree(t); break;
				}
		}
		return 0;
}
