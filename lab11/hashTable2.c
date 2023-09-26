#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTSIZE 21

typedef char	*item_t;

typedef	struct	hash
{
	item_t	*table;
	int		size;
	int		hash_key;
}			hash_t;

hash_t	*init_hashtable(int m, int hash_key)
{
	hash_t	*h;
	
	h = malloc(sizeof(hash_t));
	if (!h)
		return (NULL);
	h -> table = calloc(sizeof(item_t), m);
	if (!h -> table)
		return (NULL);
	h -> size = m;
	h -> hash_key = hash_key;
	return (h);
}

unsigned int	ft_hash(hash_t *h, const char *text)
{
	unsigned int	hash_value = 0;

	for (size_t i = 0; i < strlen(text); i++)
		hash_value = h -> hash_key * hash_value + text[i];
	return (hash_value % h -> size);
}

int	quadratic(hash_t *h, const char *text)
{
	unsigned int	index;

	if (!h)
		return (-1);
	index = ft_hash(h, text);
	for (int i = 0; i < h -> size; i++)
		if (!h -> table[(index + ((i + i * i) / 2)) % h -> size])
			return ((index + ((i + i * i) / 2)) % h -> size);
	return (-1);
}

void	insert(hash_t *h, const char *text)
{
	unsigned int	index;

	if (!h)
		return ;
	index = quadratic(h, text);
	h -> table[index] = strdup(text);
	if (!h -> table[index])
		return ;
}

int	search(hash_t *h, const char *text)
{
	unsigned int	index;

	if (!h)
		return (-1);
	index = ft_hash(h, text);
	for (int i = 0; i < h -> size; i++)
		if (h -> table[(index + ((i + i * i) / 2)) % h -> size])
			if (!strcmp(h -> table[(index + ((i + i * i) / 2)) % h -> size], text))
				return ((index + ((i + i * i) / 2)) % h -> size);
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