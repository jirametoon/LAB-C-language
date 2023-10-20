#include <stdio.h>
#include <stdlib.h>

typedef	struct		node
{
	int				seq;
	struct node		*next;
}					node_t;

typedef	struct		item
{
	node_t			**table;
	int				last_index;		
}					item_t;

typedef node_t		s_stack_t;
typedef item_t		connect_t;		

node_t	*createNode(int seq)
{
	node_t	*node;

	node = calloc(sizeof(node_t), 1);
	if (!node)
		return (NULL);
	node->seq = seq;
	return (node);
}

int	createNodeInItem(node_t ***table, int n)
{
	if (!table || !n)
		return (0);
	for (int i = 0; i < n; i++)
	{
		(*table)[i] = createNode(i);
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

void	insert(item_t **item, int u, int v)
{
	node_t	*new;

	new = createNode(v);
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
				printf(" %d", tmp->next->seq);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

void	print_stack(s_stack_t *stk)
{
	printf("stk:");
	while (stk)
	{
		printf(" %d", stk->seq);
		stk = stk->next;
	}
	printf("\n");
}

void	print_visit(s_stack_t *stk)
{
	printf("visit:");
	while (stk)
	{
		printf(" %d", stk->seq);
		stk = stk->next;
	}
	printf("\n");
}

s_stack_t	*push(s_stack_t *stk, int seq)
{
	s_stack_t	*new;

	new = calloc(sizeof(s_stack_t), 1);
	if (!new)
		return (NULL);
	new->seq = seq;
	new->next = stk;
	return (new);
}

int	pop(s_stack_t **stk)
{
	int seq;
	s_stack_t	*tmp;

	if (!stk)
		return (-1);
	tmp = *stk;
	seq = tmp->seq;
	*stk = (*stk)->next;
	free(tmp);
	return (seq);
}

int	lstsize(node_t	*node)
{
	int	count;

	count = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

int	find_max_connect(connect_t *connect)
{
	int	max = 0;
	int	tmp;
	int	max_index = 0;

	for (int i = 0; i < connect->last_index; i++)
	{
		tmp = lstsize(connect->table[i]);
		if (tmp > max)
		{
			max = tmp;
			max_index = i;
		}
	}
	return (max_index);
}

int	is_visit(int seq, s_stack_t *visit)
{
	while (visit)
	{
		if (visit->seq == seq)
			return (1);
		visit = visit->next;
	}
	return (0);
}

int	search_index(s_stack_t *visit, int last)
{
	for (int i = 0; i < last; i++)
	{
		if (!is_visit(i, visit))
			return (i);
	}
	return (-1);
}

void	dfs(item_t *item, s_stack_t **stk, s_stack_t **visit, int index)
{
	node_t		*tmp;

	if (!item || index < 0)
		return ;
	tmp = item->table[index];
	while (tmp)
	{
		if (!is_visit(tmp->seq, *visit))
        {
            *visit = push(*visit, tmp->seq);
			//print_visit(visit);
            dfs(item, stk, visit, tmp->seq); 
            *stk = push(*stk, tmp->seq);
        }
        tmp = tmp->next;
	}
}

int	index_connect(connect_t *connect, int seq)
{
	node_t	*tmp;
	
	for (int i = 0; i < connect->last_index; i++)
	{
		tmp = connect->table[i]->next;
		while (tmp)
		{
			if (tmp->seq == seq)
				return (-1);
			tmp = tmp->next;
		}
	}
	return (seq);
}

s_stack_t	*path_connect(item_t *itemT, s_stack_t **visit, int index)
{
	s_stack_t	*connect = NULL;
	int			seq;
	node_t		*tmp;

	if (!itemT)
		return (NULL);
	tmp = itemT->table[index];
	while (tmp)
	{
		seq = tmp->seq;
		if (!is_visit(seq, *visit))
		{
			*visit = push(*visit, seq);
			//print_visit(*visit);
			if (index != seq)
				connect = push(connect, seq);
			tmp = tmp->next;
			if (!tmp)
				tmp = itemT->table[seq];
		}
		else
			tmp = tmp->next;
	}
	return (connect);
}

connect_t	*kosaraju(item_t *item, item_t *itemT)
{
	s_stack_t	*stk = NULL, *visit1 = NULL, *visit2 = NULL;
	connect_t	*connect = NULL;
	int			index, seq;

	while (lstsize(stk) != item->last_index)
		dfs(item, &stk, &visit1, search_index(visit1, item->last_index));
	free_list(visit1);
	connect = createItem(item->last_index);
	//print_stack(stk);
	while (stk)
	{
		seq = pop(&stk);
		//printf("seq = %d\n", seq);
		index = index_connect(connect, seq);
		//printf("index = %d\n", index);
		if (index >= 0 && stk >= 0)
		{
			connect->table[index]->next = path_connect(itemT, &visit2, seq);
			//print_stack(connect->table[index]);
		}
	}
	//graph(connect);
	free_list(visit2);
	return (connect);
}

node_t	*merge(node_t *node1, node_t *node2)
{
    node_t	*tmp = createNode(-1);
	node_t	*current = tmp;
	node_t	*res;

    while (node1 && node2)
	{
        if (node1->seq < node2->seq)
		{
            current->next = node1;
            node1 = node1->next;
        } 
		else
		{
            current->next = node2;
            node2 = node2->next;
        }
        current = current->next;
    }
    if (node1)
        current->next = node1;
	else
		current->next = node2;
	res = tmp->next;
	free(tmp);
    return (res);
}

node_t	*mergeSort(node_t *node)
{
	node_t	*left, *right, *tmp;

	if (!node)
		return (NULL);
	if (!node->next)
		return (node);
    left = node;
	right = node->next;
    while (right)
	{
		if (!right->next)
			break ;
        left = left->next;
        right = right->next->next;
    }
    tmp = left->next;
    left->next = NULL;
    node = mergeSort(node);
    tmp = mergeSort(tmp);
    return (merge(node, tmp));
}

void	print(item_t *item, item_t *itemT)
{
	connect_t	*connect;
	int			max_connect;
	node_t		*scc;
	
	connect = kosaraju(item, itemT);
	if (!connect)
		return ;
	max_connect = find_max_connect(connect);
	scc = mergeSort(connect->table[max_connect]);
	printf("%d", scc->seq);
	scc = scc->next;
	while (scc)
	{
		printf(" %d", scc->seq);
		scc = scc->next;
	}
	printf("\n");
	free_all(connect);
}

int	main(void)
{
	int			n, m;
	int			u, v;
	item_t		*item = NULL, *itemT = NULL;

	scanf("%d %d", &n, &m);
	// create item
	item = createItem(n);
	itemT = createItem(n);

	// insert node
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		if (u > n || v > n)
		{
			free_all(item);
			free_all(itemT);
			return (1);
		}
		insert(&item, u, v);
		insert(&itemT, v, u);
	}

	// show graph
	//printf("Graph:\n");
	//graph(item);
	//printf("================\n");
	//printf("Graph Tranpose:\n");
	//graph(itemT);

	// if error
	if (!item || !itemT)
	{
		free_all(item);
		free_all(itemT);
		return (1);
	}

	// display output
	if (item->table && itemT->table)
		print(item, itemT);

	// free
	free_all(item);
	free_all(itemT);
	return (0);
}