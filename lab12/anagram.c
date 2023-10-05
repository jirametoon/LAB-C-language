#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}t_list;

typedef struct	s_table
{
	t_list	**table;
	int		last_index;
}t_table;

t_table	*createTable(void)
{
	t_table	*table;

	table = calloc(sizeof(t_table), 1);
	if (!table)
		return (NULL);
	table->table = calloc(sizeof(t_list *), 1);
	if (!table->table)
		return (NULL);
	return (table);
}

t_list	*createList(char *content)
{
	t_list	*node;

	node = calloc(sizeof(t_list), 1);
	if (!node)
		return (NULL);
	node->content = strdup(content);
	if (!node->content)
		return (NULL);
	return (node);
}

void	add_list(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!new)
		return ;
	node = *lst;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*lst = new;
}

int	is_in_string(char c, char *content)
{
	for (size_t i = 0; i < strlen(content); i++)
		if (c == content[i])
			return (1);
	return (0);
}

int	is_word(char *content, t_list *lst)
{
	for (size_t i = 0; i < strlen(lst->content); i++)
		if (!is_in_string(content[i], lst->content))
			return (0);
	return (1);
}

void	insert(t_table **table, char *content)
{
	t_list	*node;
	int 	i;

	if (!table)
		return ;
	if (!*table)
	{
		node = createList(content);
		if (!node)
			return ;
		(*table)->table[0] = node; 
		(*table)->last_index++;
	}
	else
	{
		node = createList(content);
		if (!node)
			return ;
		for (i = 0; i < (*table)->last_index; i++)
			if (is_word(content, (*table)->table[i]))
			{
				add_list(&(*table)->table[i], node);
				break ;
			}
		if (i == (*table)->last_index)
		{
			(*table)->table[(*table)->last_index] = node; 
			(*table)->last_index++;
		}
	}
}

t_list	*find_word(t_table *table, char *content)
{
	for (int i = 0; i < table->last_index; i++)
		if (is_word(content, table->table[i]))
			return (table->table[i]);
	return (NULL);
}

void	print(t_table *table, char *content)
{
	t_list	*lst;

	if (!table)
		return ;
	lst = find_word(table, content);
	if (lst)
	{
		printf("%s", lst->content);
		lst = lst->next;	
	}
	while (lst)
	{
		printf(" %s", lst->content);
		lst = lst->next;
	}
	printf("\n");
}

int	main(void)
{
	int		m, n;
	char	content[50];
	t_table *table = NULL;

	scanf("%d %d", &m, &n);
	table = createTable();
	for (int i = 0; i < m; i++)
	{
		scanf("%s", content);
		insert(&table, content);
	}
	for (int j = 0; j < n; j++)
	{
		scanf("%s", content);
		print(table, content);
	}
	return (0);
}
