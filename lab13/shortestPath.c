#include <stdio.h>
#include <stdlib.h>

typedef	struct		node
{
	int				seq;
	int				weight;
	struct node		*next;
}					node_t;

typedef	struct		item
{
	node_t			**table;
	int				last_index;		
}					item_t;

typedef struct		s_stack
{
	int				seq;
	int				weight;
	int				pre_seq;
	struct s_stack	*next;
}					s_stack_t;

node_t	*createNode(int seq, int w)
{
	node_t	*node;

	node = calloc(sizeof(node_t), 1);
	if (!node)
		return (NULL);
	node->seq = seq;
	node->weight = w;
	return (node);
}

int	createNodeInItem(node_t ***table, int n)
{
	if (!table || !n)
		return (0);
	for (int i = 0; i < n; i++)
	{
		(*table)[i] = createNode(i, 0);
		if (!(*table)[i])
		{
			for (int j = 0; j < i; j++)
				free((*table)[j]);
			return (0);
		}
	}
	return (1);
}

item_t	*createItem(int n)
{
	item_t	*item;

	if (!n)
		return (NULL);
	item = malloc(sizeof(item_t));
	if (!item)
		return (NULL);
	item->table = calloc(sizeof(node_t *), n);
	if (!item->table)
	{
		free(item);
		return (NULL);
	}
	if (!createNodeInItem(&item->table, n))
	{
		free(item->table);
		free(item);
		return (NULL);
	}
	item->last_index = n;
	return (item);
}

void	free_list(node_t *node)
{
	node_t	*tmp;
	
	if (!node)
		return ;
	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	node = NULL;
}

void	free_stack(s_stack_t *stk)
{
	s_stack_t	*tmp;
	
	if (!stk)
		return ;
	while (stk)
	{
		tmp = stk->next;
		free(stk);
		stk = tmp;
	}
	stk = NULL;
}

void	free_all(item_t *item)
{
	if (!item)
		return ;
	for (int i = 0; i < item->last_index; i++)
		free_list(item->table[i]);
	free(item->table);
	free(item);
}

node_t	*insertNode(node_t *node, node_t *new)
{
	node_t	*tmp;

	if (!node)
		return (NULL);
	tmp = node;
	while (node->next)
		node = node->next;
	node->next = new;
	return (tmp);
}

void	insert(item_t **item, int u, int v, int w)
{
	node_t	*new;

	new = createNode(v, w);
	if (!new)
		return ;
	(*item)->table[u] = insertNode((*item)->table[u], new);	
}

void	graph(item_t *item)
{
	node_t	*tmp;

	for (int i = 0; i < item->last_index; i++)
	{
		printf("[%d] -> ", i);
		tmp = item->table[i];
		while (tmp)
		{
			if (tmp->next)
				printf(" %d(%d)", tmp->next->seq, tmp->next->weight);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

s_stack_t	*push(s_stack_t *stk, int seq, int weight, int pre_seq)
{
	s_stack_t	*new;

	new = calloc(sizeof(s_stack_t), 1);
	if (!new)
		return (NULL);
	new->seq = seq;
	new->weight = weight;
	new->pre_seq = pre_seq;
	if (stk)
		new->next = stk;
	return (new);
}

int	find_list(s_stack_t	*stk, int seq)
{
	while (stk)
	{
		if (stk->seq == seq)
			return (stk->weight);
		stk = stk->next;
	}
	return (-1);
}

int	total_weight(s_stack_t	*stk, int head)
{
	while (stk)
	{
		if (head == stk->seq)
			return (stk->weight);
		stk = stk->next;
	}
	return (0);
}

s_stack_t	*change_path(s_stack_t *stk, int seq, int weight, int pre_seq)
{
	s_stack_t	*tmp;

	tmp = stk;
	while (tmp)
	{
		if (seq == tmp->seq)
		{
			tmp->weight = weight;
			tmp->pre_seq = pre_seq;
			break ;
		}
		tmp = tmp->next;
	}
	return (stk);
}

void	dijkstra(item_t *item, s_stack_t **stk, int s, int t)
{
	node_t		*head, *tmp;
	int			short_path;
	int			path;

	head = item->table[s];
	tmp = head->next;
	while (tmp)
	{
		short_path = find_list(*stk, tmp->seq);
		path = total_weight(*stk, head->seq) + tmp->weight;
		if (short_path < 0 || path < short_path)
		{
			if (short_path < 0)
				*stk = push(*stk, tmp->seq, path, head->seq);
			else if (path < short_path)
				*stk = change_path(*stk, tmp->seq, path, head->seq);
			if (s != t)
				dijkstra(item, stk, tmp->seq, t);
		}
		tmp = tmp->next;
	}
}

void	print(item_t *item, int s, int t)
{
	s_stack_t	*stk;

	stk = push(NULL, s, 0, -1);
	dijkstra(item, &stk, s, t);
	printf("%d\n", find_list(stk, t));
	free_stack(stk);
}

int	main(void)
{
	int			n, m, p;
	int			u, v, w;
	int			s, t;
	item_t		*item = NULL;

	scanf("%d %d %d", &n, &m, &p);
	// create item
	item = createItem(n);

	// insert node
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		if (u > n || v > n)
		{
			free_all(item);
			return (1);
		}
		insert(&item, u, v, w);
		insert(&item, v, u, w);
	}

	// show graph
	//graph(item);

	// if error
	if (!item)
	{
		free_all(item);
		return (1);
	}

	// display output
	if (item->table)
	{
		for (int k = 0; k < p; k++)
		{
			scanf("%d %d", &s, &t);
			
			if (s > n || t > n)
				printf("-1\n");
			else
				print(item, s, t);
		}
	}

	// free
	free_all(item);
	return (0);
}