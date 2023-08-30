#include <stdio.h>
#include <stdlib.h>

typedef struct	node
{
	char		data;
	struct node	*next;
}node_t;

typedef node_t	s_stack_t;

void	free_stack(s_stack_t *s)
{
	node_t	*node;

	while (s)
	{
		node = s;
		s = s -> next;
		free(node);
	}
}

void	push(s_stack_t **s, char value)
{
		node_t	*node;

		node = (node_t *)malloc(sizeof(node_t));
		if (node)
		{
				node -> data = value;
				node -> next = *s;
				*s = node;
		}
}

void	pop(s_stack_t **s)
{
		node_t	*node;

		node = *s;
		if (node)
		{
				*s = (*s) -> next;
				free(node);
		}
}

int	check_paren(s_stack_t *s, char value)
{
		while (s)
		{
				if ((s -> data == '(' && value == ')') \
				 || (s -> data == '[' && value == ']') \
				 || (s -> data == '{' && value == '}'))
						return (1);
				s = s -> next;
		}
		return (0);
}

int	main(void)
{
		s_stack_t	*s = NULL;
		int		size;
		char	c;

		scanf("%d", &size);
		for (int i = 0; i < size; i++)
		{
				scanf(" %c", &c);
				if (!check_paren(s, c))
						push(&s, c);
				else
						pop(&s);
		}
		if (!s)
				printf("1\n");
		else
		{
				printf("0\n");
				free_stack(s);
		}
		return (0);
}
