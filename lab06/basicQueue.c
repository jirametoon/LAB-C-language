#include <stdio.h>
#include <stdlib.h>

typedef struct	node
{
		int			data;
		struct node	*next;
}node_t;

typedef node_t queue_t;

queue_t	*enqueue(queue_t *q, int value)
{
		node_t	*node;

		node = (node_t *)malloc(sizeof(node_t));
		if (!node)
				return (q);
		node -> data = value;
		node -> next = q;
		return (node);
}

queue_t	*dequeue(queue_t *q)
{
		node_t	*node;

		node = q;
		if (!node)
				printf("Queue is empty.\n");
		else
		{
				printf("%d\n", q -> data);
				q = q -> next;
				free(node);
		}
		return (q);
}

void	show(queue_t *q)
{
		node_t	*node;

		node = q;
		if (!node)
				printf("Queue is empty.\n");
		else
		{
				printf("%d", node -> data);
				while (node -> next)
				{
						node = node -> next;
						printf(" %d", node -> data);
				}
				printf("\n");
		}
}

void	empty(queue_t *q)
{
		if (q)
				printf("Queue is not empty.\n");
		else
				printf("Queue is empty.\n");
}

void	size(queue_t *q)
{
		node_t	*node;
		int		size;

		node = q;
		size = 0;
		while (node)
		{
				node = node -> next;
				size++;
		}
		printf("%d\n", size);
}

int	main(void)
{
		queue_t	*q = NULL;
		int 	n, i, command, value;
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
				scanf("%d", &command);
				switch(command)
				{
						case 1: scanf("%d", &value); q = enqueue(q, value); break;
						case 2: q = dequeue(q); break;
						case 3: show(q); break;
						case 4: empty(q); break;
						case 5: size(q); break;
				}
		}
		return 0;
}

/*
 *		1 :	enqueue()
 *		2 :	dequeue()
 *		3 :	show()
 *		4 :	empty()
 *		5 :	size()
 */
