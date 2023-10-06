#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef	char	*t_word;

void	print_all(t_word *table)
{
	int	i = -1;

	if (!table)
		return ;
	while (table[++i])
		printf("table[%d] = %s\n", i, table[i]);
}

char	*sort_char(char *str)
{
	char	*new;
	char	c;

	new = strdup(str);
	if (!new)
		return (NULL);
	for (size_t i = 1; i < strlen(new); i++)
	{
		c = new[i];
		for (size_t j = i; j > 0; j--)
		{
			if (c < new[j - 1])
			{
				new[j] = new[j - 1];
				new[j - 1] = c;
			}
			else
				break ;
		}
	}
	return (new);
}

int	is_anagram(char *str, char *text)
{
	char	*tmp1; 
	char	*tmp2;

	tmp1 = sort_char(str);
	tmp2 = sort_char(text);
	if (!tmp1 || !tmp2)
		return (0);
	if (!strcmp(tmp1, tmp2))
	{
		free(tmp1);
		free(tmp2);
		return (1);
	}
	free(tmp1);
	free(tmp2);
	return (0);
}

void	print_anagram(char *str, t_word *table)
{
	int	i = 0;

	if (!table)
		return ;
	while (table[i])
	{
		if (is_anagram(str, table[i]))
			printf("%s ", table[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	t_word	*table = NULL;
	char	str[51], text[51];
	int		m, n, k;

	scanf("%d %d", &m, &n);
	table = calloc(sizeof(t_word), m + 1);
	if (!table)
		return (1);

	// insert word
	for (int i = 0; i < m; i++)
	{
		scanf("%s", str);
		table[i] = strdup(str);
	}

	//print_all(table);

	// find anagram
	for (int j = 0; j < n; j++)
	{
		scanf("%s", text);
		print_anagram(text, table);
	}

	// free
	k = -1;
	while (table[++k])
		free(table[k]);
	free(table);
	return (0);
}