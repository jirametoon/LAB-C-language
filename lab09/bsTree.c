#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

typedef	struct	node
{
	int			data;
	struct node	*left;
	struct node	*right;
}				node_t;

typedef	node_t	bst_t;
// Write your code here
// ...
bst_t	*createNode(int data)
{
	bst_t	*node;

	node = malloc(sizeof(bst_t));
	if (!node)
		return (NULL);
	node -> data = data;
	node -> right = NULL;
	node -> left = NULL;
	return (node);
}

bst_t	*appendNode(bst_t *t, int data)
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

bst_t	*insert(bst_t *t, int data)
{
	bst_t	*node, *tmp;

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

bst_t	*findDeleteNode(bst_t *t, int data)
{
	if (!t)
		return (NULL);
	if (data > t -> data)
		return (findDeleteNode(t -> right, data));
	else if (data < t -> data)
		return (findDeleteNode(t -> left, data));
	return (t);
}

bst_t	*findDeleteParent(bst_t *t, bst_t *parent, int data)
{
	if (!t)
		return (NULL);
	if (data > t -> data)
		return (findDeleteParent(t -> right, t, data));
	else if (data < t -> data)
		return (findDeleteParent(t -> left, t, data));
	return (parent);
}

void	destroy(bst_t **parent, bst_t *node, bst_t *tmp)
{
	if ((*parent) -> left == node)
		(*parent) -> left = tmp;
	else if ((*parent) -> right == node)
		(*parent) -> right = tmp;
	free(node);
}

int	find(bst_t *t, int data)
{
	if (!t)
		return (FALSE);
	if (data > t -> data)
		return (find(t -> right, data));
	else if (data < t -> data)
		return (find(t -> left, data));
	return (TRUE);
}

int	find_min(bst_t *t)
{
	if (!t)
		return (FALSE);
	if (t -> left)
		return (find_min(t -> left));
	return (t -> data);
}

int	find_max(bst_t *t)
{
	if (!t)
		return (FALSE);
	if (t -> right)
		return (find_max(t -> right));
	return (t -> data);
}

bst_t	*delete(bst_t *t, int data)
{
	bst_t	*node, *parent;
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
		node = delete(node, min);
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

int	main(void)
{
	bst_t	*t = NULL;
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
			case 3: scanf("%d", &data); printf("%d\n", find(t, data)); break;
			case 4: printf("%d\n", find_min(t)); break;
			case 5: printf("%d\n", find_max(t)); break;
		}
	}
	return (0);
}
