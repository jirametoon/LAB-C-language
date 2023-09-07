#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#define TRUE	1
#define FALSE	0

#ifndef __bin_tree__

typedef struct	node
{
	int		data;
	struct node	*left;
	struct node	*right;
}node_t;

typedef node_t tree_t;

#endif
// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week8.h header
// ...

int	size(tree_t *t)
{
	if (!t)
		return (FALSE);
	return (size(t -> left) + size(t -> right) + 1);
}
int	height(tree_t *t)
{
	int	hl;
	int	hr;

	if (!t)
		return (-1);
	hl = height(t -> left);
	hr = height(t -> right);
	return ((hl > hr) ? (hl + 1) : (hr + 1));
}

int	check_perfect(tree_t *t, int height, int level)
{
	if (!t)
		return (TRUE);
	if ((!t -> left && t -> right) || (t -> left && !t -> right))
		return (FALSE);
	if (!t -> left && !t -> right)
		return (level == height);
	return (check_perfect(t -> left, height, level + 1) && check_perfect(t -> right, height, level + 1));
}

int	check_complete(tree_t *t, int size, int index)
{
	if (!t)
		return (TRUE);
	if (size <= index)
		return (FALSE);
	return (check_complete(t -> left, size, 2 * index + 1) && check_complete(t -> right, size, 2 * index + 2));
}

int	is_oneNode(tree_t *t)
{
	if (!t)
		return (TRUE);
	if (t -> left && t -> right)
		return (FALSE);
	return ((t -> left) ? (is_oneNode(t -> left)) : is_oneNode(t -> right));
}

int	is_left(tree_t *t)
{
	if (!t)
		return (TRUE);
	if (t -> right)
		return (FALSE);
	return (is_left(t -> left));
}

int	is_right(tree_t *t)
{
	if (!t)
		return (TRUE);
	if (t -> left)
		return (FALSE);
	return (is_right(t -> right));
}

int	is_full(tree_t *t)
{
	int	left;
	int	right;

	if (!t)
		return (FALSE);
	if (!t -> left && !t -> right)
		return (TRUE);
	left = is_full(t -> left);
	right = is_full(t -> right);
	return (left && right);
}

int	is_perfect(tree_t *t)
{
	int	h;

	h = height(t);
	return (check_perfect(t, h, 0));
}

int	is_complete(tree_t *t)
{
	int	s;

	s = size(t);
	return (check_complete(t, s, 0));
}

int	is_degenerate(tree_t *t)
{
	if (!t)
		return (FALSE);
	return (is_oneNode(t));
}

int	is_skewed(tree_t *t)
{
	return ((t -> left) ? (is_left(t)) : (is_right(t)));
}

int	main(void)
{
	tree_t	*t = NULL;
	int	n, i;
	int	parent, child;
	int	branch; // 0 root, 1 left, 2 right

	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d %d %d", &parent, &child, &branch);
		t = attach(t, parent, child, branch);
	}
	printf("%d %d %d %d %d\n", is_full(t), is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));
	return (0);
}
