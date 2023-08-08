#include <stdio.h>
#include <stdlib.h>

typedef struct	node
{
	char		data;
	struct node	*next;
}node_t;

typedef node_t	stack_t;
typedef node_t	queue_t;

queue_t *rear = NULL;

void	free_all(node_t *node)
{
		node_t	*tmp;

		while (node)
		{
				tmp = node;
				node = node -> next;
				free(tmp);
		}
}

stack_t	*push(stack_t *s, char c)
{
		node_t	*node;

		node = (node_t *)malloc(sizeof(node_t));
		if (!node)
				return (s);
		node -> data = c;
		node -> next = s;
		return (node);
}

queue_t	*enqueue(queue_t *q, char c)
{
		node_t	*node;

		node = (node_t *)malloc(sizeof(node_t));
		if (!node)
				return (q);
		node -> data = c;
		node -> next = NULL;
		if (!q)
		{
				q = node;
				rear = node;
		}
		else
		{
				rear -> next = node;
				rear = node;
		}
		return (q);
}

int	check_password(stack_t *s, queue_t *q)
{
		while (s && q)
		{
				if (s -> data != q -> data)
						return (0);
				s = s -> next;
				q = q -> next;
		}
		return (1);
}

void	show(node_t *node)
{
	while (node)
	{
		printf("%c", node -> data);
		node = node -> next;
	}
	printf("\n");
}

int	main(void)
{
		stack_t	*s = NULL;
		queue_t	*q = NULL;
		char	c;

		c = 0;
		while ((c = getchar()) != 'x')
				s = push(s, c);
		while ((c = getchar()) != 'y')
				q = enqueue(q, c);
		//show(s);
		//show(q);
		printf("%d\n", check_password(s, q));
		free_all(s);
		free_all(q);
		return (0);
}
