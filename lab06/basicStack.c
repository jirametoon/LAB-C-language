#include <stdio.h>
#include <stdlib.h>

typedef struct	node
{
	int			data;
	struct node	*next;
}node_t;

typedef node_t stack_t;

stack_t	*push(stack_t *s, int value)
{
		node_t *node;

		node = (node_t *)malloc(sizeof(node_t));
		if (!node)
				return (s);
		node -> data = value;
		node -> next = s;
		s = node;
		return (s);
}

void	top(stack_t *s)
{
		if (s)
				printf("%d\n", s -> data);
		else
				printf("Stack is empty.\n");
}

stack_t	*pop(stack_t *s)
{
		node_t	*node;

		if (!(node = s))
				return (NULL);
		s = s -> next;
		free(node);
		return (s);
}

void	empty(stack_t *s)
{
		if (s)
				printf("Stack is not empty.\n");
		else
				printf("Stack is empty.\n");
}

void	size(stack_t *s)
{
		int		size;

		size = 0;
		while (s)
		{
				s = s -> next;
				size++;
		}
		printf("%d\n", size);
}

int	main(void)
{
		stack_t	*s = NULL;
		int		n, i, command, value;
		
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
				scanf("%d", &command);
				switch(command)
				{
						case 1: scanf("%d", &value); s = push(s, value); break;
						case 2: top(s); break;
						case 3: s = pop(s); break;
						case 4: empty(s); break;
						case 5: size(s); break;
				}
		}
		return 0;
}

/*
 *		1 :	push()
 *		2 :	top()
 *		3 :	pop()
 *		4 :	empty()
 *		5 :	size()
 */
