#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

#define TRUE	1
#define FALSE	0

#ifndef __avl_tree__

typedef struct	node
{
	int			data;
	int			height;
	struct node *left;
	struct node *right;
}				node_t;

typedef node_t avl_t;

#endif

int	height(avl_t *t)
{
	int	hl, hr;

	if (!t)
		return (-1);
	hl = height(t -> left);
	hr = height(t -> right);
	return ((hl > hr) ? (hl + 1) : (hr + 1));
}

int	is_avl(avl_t *t)
{
	if (!t)
		return (TRUE);
	if (!t -> left && !t -> right)
		return (TRUE);
	if (!t -> left)
	{
		if (!t -> right -> height)
			return (TRUE);
		else
			return (FALSE);
	}
	if (!t -> right)
	{
		if (!t -> left -> height)
			return (TRUE);
		else
			return (FALSE);
	}
	if ((t -> left -> height) - (t -> right -> height) < -1 \
		|| (t -> left -> height) - (t -> right -> height) > 1)
		return (FALSE);
	return (is_avl(t -> left) && is_avl(t -> right));
}

avl_t	*searchBrokeNode(avl_t *t)
{
	if (!t)
		return (NULL);
	if (is_avl(t))
		return (NULL);
	if (!is_avl(t -> left))
		return (searchBrokeNode(t -> left));
	else if (!is_avl(t -> right))
		return (searchBrokeNode(t -> right));
	return (t);
}

avl_t	*searchParentBrokeNode(avl_t *t, avl_t *parent)
{
	if (!t)
		return (NULL);
	if (is_avl(t))
		return (NULL);
	if (!is_avl(t -> left))
		return (searchParentBrokeNode(t -> left, t));
	else if (!is_avl(t -> right))
		return (searchParentBrokeNode(t -> right, t));
	return (parent);
}

avl_t	*rightRotation(avl_t *t)
{
	avl_t	*node, *tmp;

	node = t -> left;
	tmp = node -> right;
	t -> left = tmp;
	node -> right = t;
	return (node);
}

avl_t	*leftRotation(avl_t *t)
{
	avl_t	*node, *tmp;

	node = t -> right;
	tmp = node -> left;
	t -> right = tmp;
	node -> left = t;
	return (node);
}

void	changeHeight(avl_t **t)
{
	if (*t)
	{
		(*t) -> height = height(*t);
		changeHeight(&(*t) -> left);
		changeHeight(&(*t) -> right);
	}
}

avl_t	*fix_avl(avl_t *t)
{
	avl_t	*node, *parent;
	char	check;

	if (!t)
		return (NULL);
	node = searchBrokeNode(t);
	if (!node)
		return (t);
	parent = searchParentBrokeNode(t, t);
	check = 0;
	if (parent -> right == node)
		check = 'r';
	else if (parent -> left == node)
		check = 'l';
	if (height(node -> left) > height(node -> right))
	{
		if (height(node -> left -> left) < height(node -> left -> right))
		{
			node -> left = leftRotation(node -> left);
			node = rightRotation(node);
		}
		else
			node = rightRotation(node);
	}
	else
	{
		if (height(node -> right -> left) > height(node -> right -> right))
		{
			node -> right = rightRotation(node -> right);
			node = leftRotation(node);
		}
		else
			node = leftRotation(node);
	}
	if (check == 'l')
		parent -> left = node;
	else if (check == 'r')
		parent -> right = node;
	else
	{
		changeHeight(&node);
		return (fix_avl(node));
	}
	changeHeight(&t);
	return (fix_avl(t));
}

avl_t	*createNode(int data)
{
	avl_t	*node;

	node = malloc(sizeof(avl_t));
	if (!node)
		return (NULL);
	node -> data = data;
	node -> height = 0;
	node -> left = NULL;
	node -> right = NULL;
	return (node);
}

avl_t	*appendNode(avl_t *t, int data)
{
	if (!t)
		return (NULL);
	if (data == t -> data)
		return (NULL);
	if (data > t -> data)
	{
		if (!t -> right)
			return (t);
		else
			return (appendNode(t -> right, data));
	}
	else
	{
		if (!t -> left)
			return (t);
		else
			return (appendNode(t -> left, data));
	}
}

avl_t	*insertTree(avl_t *t, int data)
{
	avl_t	*node, *tmp;

	node = appendNode(t, data);
	tmp = createNode(data);
	if (!node)
		return (tmp);
	else
	{
		if (data > node -> data)
			node -> right = tmp;
		else if (data < node -> data)
			node -> left = tmp;
	}
	return (t);
}

avl_t	*insert(avl_t *t, int data)
{
	avl_t	*node;

	node = insertTree(t, data);
	changeHeight(&node);
	if (is_avl(node))
		return (node);
	t = fix_avl(node);
	return (t);
}

avl_t	*findDeleteNode(avl_t *t, int data)
{
	if (!t)
		return (NULL);
	if (data > t -> data)
		return (findDeleteNode(t -> right, data));
	else if (data < t -> data)
		return (findDeleteNode(t -> left, data));
	return (t);
}

avl_t	*findDeleteParent(avl_t *t, avl_t *parent, int data)
{
	if (!t)
		return (NULL);
	if (data > t -> data)
		return (findDeleteParent(t -> right, t, data));
	else if (data < t -> data)
		return (findDeleteParent(t -> left, t, data));
	return (parent);
}

void	destroy(avl_t **parent, avl_t *node, avl_t *tmp)
{
	if ((*parent) -> left == node)
		(*parent) -> left = tmp;
	else if ((*parent) -> right == node)
		(*parent) -> right = tmp;
	free(node);
}

int	find_min(avl_t *t)
{
	if (!t)
		return (FALSE);
	if (t -> left)
		return (find_min(t -> left));
	return (t -> data);
}

avl_t	*deleteTree(avl_t *t, int data)
{
	avl_t	*node, *parent;
	int		min;

	if (!t)
		return (NULL);
	node = findDeleteNode(t, data);
	if (!node)
		return (t);
	parent = findDeleteParent(t, t, data);
	if (node -> left && node -> right)
	{
		min = find_min(node -> right);
		node = deleteTree(node, min);
		node -> data = min;
	}
	else if (node -> left)
		destroy(&parent, node, node -> left);
	else if (node -> right)
		destroy(&parent, node, node -> right);
	else
		destroy(&parent, node, NULL);
	return (t);
}

avl_t	*delete(avl_t *t, int data)
{
	avl_t	*node;

	node = deleteTree(t, data);
	changeHeight(&node);
	if (is_avl(node))
		return (node);
	t = fix_avl(node);
	return (t);
}

int	main(void)
{
	avl_t	*t = NULL;
	int		n, i;
	int		command, data;
	
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &command);
		switch (command)
		{
			case 1: scanf("%d", &data); t = insert(t, data); break;
			case 2: scanf("%d", &data); t = delete(t, data); break;
			case 3: print_tree(t); break;
		}
	}
	return (0);
}
