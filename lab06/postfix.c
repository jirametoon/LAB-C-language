#include <stdio.h>
#include <stdlib.h>

typedef struct	node
{
	float			value;
	struct node	*next;
}node_t;

typedef node_t	stack_t;

void	free_stack(stack_t *s)
{
		node_t	*node;

		while (s)
		{
				node = s;
				s = s -> next;
				free(node);
		}
}

void	push(stack_t **s, char c)
{
		node_t	*node;

		node = (node_t *)malloc(sizeof(node_t));
		if (node)
		{
				node -> value = c - '0';
				node -> next = *s;
				*s = node;
		}
}

void	operate(stack_t **s, char c)
{
		node_t	*node;

		node = *s;
		if (c == '+')
		{
				*s = (*s) -> next;
				(*s) -> value += node -> value;
				free(node);
		}
		else if (c == '-')
		{
				*s = (*s) -> next;
				(*s) -> value -= node -> value;
				free(node);
		}
		else if (c == '*')
		{
				*s = (*s) -> next;
				(*s) -> value *= node -> value;
				free(node);
		}
		else if (c == '/')
		{
				*s = (*s) -> next;
				(*s) -> value /= node -> value;
				free(node);
		}
}

int	main(void)
{
		stack_t	*s = NULL;
		int		size;
		char	c;

		scanf("%d", &size);
		for (int i = 0; i < size; i++)
		{
				scanf(" %c", &c);
				if (c >= '0' && c <= '9')
						push(&s, c);
				else if (s && s -> next && (c == '+' || c == '-' || c == '*' || c == '/'))
						operate(&s, c);
				else
				{
						printf("Error\n");
						free_stack(s);
						return (1);
				}
		}
		if (s && !(s -> next))
		{
				printf("%.2f\n", s -> value);
				free(s);
		}
		else if (s -> next)
		{
			printf("Error\n");
			free_stack(s);
		}
		else
				printf("0.00\n");
		return (0);
}
