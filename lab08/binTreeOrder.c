#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__

typedef struct	node
{
	int		data;
	struct node	*left;
	struct node	*right;
}node_t;

typedef node_t	tree_t;

#endif
// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week8.h header
// ...

void	preorder(tree_t *t)
{
	if (t)
	{
		printf(" %d", t -> data);
		preorder(t -> left);
		preorder(t -> right);
	}
}

void	print_preorder(tree_t *t)
{
	if (t)
	{
		printf("%d", t -> data);
		preorder(t -> left);
		preorder(t -> right);
		printf("\n");
	}
}

void	postorder(tree_t *t)
{
	if (t)
	{
		postorder(t -> left);
		postorder(t -> right);
		printf("%d ", t -> data);
	}
}

void	print_postorder(tree_t *t)
{
	if (t)
	{
		postorder(t -> left);
		postorder(t -> right);
		printf("%d\n", t -> data);
	}
}

void	print_inorder(tree_t *t)
{
	if (t)
	{
		print_inorder(t -> left);
		printf(" %d", t -> data);
		print_inorder(t -> right);
		printf("\n");
	}
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
	print_preorder(t);
	print_postorder(t);
	print_inorder(t);
	return (0);
}
