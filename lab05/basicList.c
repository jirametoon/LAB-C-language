#include <stdio.h>
#include <stdlib.h>

typedef struct	node
{
	int		data;
	struct node	*next;
} node_t;

void	free_node(node_t *node)
{
	node_t	*ptr;
	int	size;

	ptr = node;
	size = 0;
	while (ptr)
	{
		ptr = ptr -> next;
		size++;
	}
	for (int i = size; i > 0; i--)
	{
		ptr = node;
		for (int j = 0; j < i - 1; j++)
			ptr = ptr -> next;
		free(ptr);
	}
}

node_t	*append(node_t *startNode)
{
	node_t	*tmp, *node;

	tmp = (node_t *)malloc(sizeof(node_t));
	if (!tmp)
		return (NULL);
	scanf("%d", &tmp -> data);
	tmp -> next = NULL;
	if (!startNode)
		startNode = tmp;
	else
	{
		node = startNode;
		while (node -> next)
			node = node -> next;
		node -> next = tmp;
	}
	return (startNode);
}

void	get(node_t *startNode)
{
	node_t	*node;
	int	index;

	node = startNode;
	scanf("%d", &index);
	for (int i = 0; i < index; i++)
	{
		node = node -> next;
		if (!node)
			break;
	}
	if (node && index >= 0)
		printf("%d", node -> data);
	else
		printf("Out of range.");
	printf("\n");
}

void	show(node_t *startNode)
{
	node_t	*node;

	node = startNode;
	while (node)
	{
		printf("%d", node -> data);
		node = node -> next;
		if (node)
			printf(" ");
	}
	printf("\n");
}

node_t	*reverse(node_t *startNode)
{
	node_t	*newNode, *node, *tmp1, *tmp2;
	int	size;

	newNode = NULL;
	node = startNode;
	size = 0;
	while (node)
	{
		node = node -> next;
		size++;
	}
	for (int i = size; i > 0; i--)
	{
		tmp1 = startNode;
		for (int j = 0; j < i - 1; j++)
			tmp1 = tmp1 -> next;
		tmp2 = (node_t *)malloc(sizeof(node_t));
		if (!tmp2)
			return (startNode);
		tmp2 -> data = tmp1 -> data;
		tmp2 -> next = NULL;
		if (!newNode)
			newNode = tmp2;
		else
		{
			node = newNode;
			while (node -> next)
				node = node -> next;
			node -> next = tmp2;
		}
			
	}
	free_node(startNode);
	return (newNode);
}

node_t	*cut(node_t *startNode)
{
	node_t	*newNode, *node, *tmp1, *tmp2;
	int	start, end, size;

	scanf("%d %d", &start, &end);
	node = startNode;
	size = 0;
	while (node)
	{
		node = node -> next;
		size++;
	}
	if (start < 0 || start >= size || end < 0 || end >= size)
	{
		printf("Out of range.\n");
		return (startNode);
	}
	if (start > end)
	{
		start = start + end;
		end = start - end;
		start = start - end;
	}
	newNode = NULL;
	tmp1 = startNode;
	for (int i = 0; i < start; i++)
		tmp1 = tmp1 -> next;
	for (int i = start; i <= end; i++)
	{
		tmp2 = (node_t *)malloc(sizeof(node_t));
		if (!tmp2)
			return (startNode);
		tmp2 -> data = tmp1 -> data;
		tmp2 -> next = NULL;
		if (!newNode)
			newNode = tmp2;
		else
		{
			node = newNode;
			while (node -> next)
				node = node -> next;
			node -> next = tmp2;
		}
		tmp1 = tmp1 -> next;
	}
	free_node(startNode);
	return (newNode);
}

int	main(void)
{
	node_t	*startNode;
	int	n, i;
	char	command;

	startNode = NULL;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf(" %c", &command);
		switch (command)
		{
			case 'A': startNode = append(startNode); break;
			case 'G': get(startNode); break;
			case 'S': show(startNode); break;
			case 'R': startNode = reverse(startNode); break;
			case 'C': startNode = cut(startNode); break;
			default : break;
		}
	}
	free_node(startNode);
	return (0);
}
