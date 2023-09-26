#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTSIZE 21

typedef struct	item
{
	char		*text;
	struct item	*next;
}				item_t;

typedef struct	hash
{
	item_t		**table;
	int			size;
	int			hash_key;
}				hash_t;

hash_t	*init_hashtable(int m, int hash_key)
{
	hash_t	*h;
	
	h = malloc(sizeof(hash_t));
	if (!h)
		return (NULL);
	h -> table = calloc(sizeof(item_t *), m);
	if (!h -> table)
		return (NULL);
	h -> size = m;
	h -> hash_key = hash_key;
	return (h);
}

item_t	*insert_item(item_t *i, const char *text)
{
	item_t	*tmp;
	
	tmp = malloc(sizeof(item_t));
	if (!tmp)
		return (NULL);
	tmp -> text = strdup(text);
	if (!tmp -> text)
	{
		free(tmp);
		return (NULL);
	}
	tmp -> next = NULL;
	if (i)
		tmp -> next = i;
	return (tmp);
}

unsigned int	ft_hash(hash_t *h, const char *text)
{
	unsigned int	hash_value = 0;

	for (size_t i = 0; i < strlen(text); i++)
		hash_value = h -> hash_key * hash_value + text[i];
	return (hash_value % h -> size);
}

void	insert(hash_t *h, const char *text)
{
	unsigned int	index;

	if (!h)
		return ;
	index = ft_hash(h, text);
	h -> table[index] = insert_item(h -> table[index], text);
}

int	find_item(item_t *i, const char *text)
{
	if (!i)
		return (0);
	while (i)
	{
		if (!strcmp(i -> text, text))
			return (1);
		i = i -> next;
	}
	return (0);
}

int	search(hash_t *h, const char *text)
{
	unsigned int	index;

	if (!h)
		return (-1);
	index = ft_hash(h, text);
	if (find_item(h -> table[index], text))
		return (index);
	return (-1);
}

int	main(void)
{
	hash_t	*hashtable = NULL;
	char	*text = NULL;
	int		m, n, i, hash_key;
	int		command;
	
	scanf("%d %d %d", &m, &n, &hash_key);
	hashtable = init_hashtable(m, hash_key);
	text = (char *)malloc(sizeof(char) * TEXTSIZE);
	
	for (i = 0; i < n; i++)
	{
		scanf("%d %s", &command, text);
		switch (command)
		{
			case 1:	insert(hashtable, text);					break;
			case 2:	printf("%d\n", search(hashtable, text));	break;
		}
	}
	return (0);
}