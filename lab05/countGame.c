#include <stdio.h>
#include <stdlib.h>

typedef struct	player
{
	int		no;		// player number
	int		shot;		// amount of alcohol
	int		status;		// win or out
	struct player	*next;
} player_t;

void	show(player_t *player)
{
	player_t	*node;

	node = player;
	while (node)
	{
		printf("NO	: %d\nShot	: %d\nStatus	: %d\n", node -> no, node -> shot, node -> status);
		printf("---------------------\n");
		node = node -> next;
	}
}

void	show_player(player_t *player, int count)
{
	player_t *node;
	
	node = player;
	while (node)
	{
		printf("count : %d\n", count);
		printf("%d : %d\n", node -> no, node -> shot);
		node = node -> next;
	}
	printf("---------------------\n");
}

void	free_node(player_t *player)
{
	player_t	*node;
	int		size;

	node = player;
	size = 0;
	while (node)
	{
		node = node -> next;
		size++;
	}
	for (int i = size; i > 0; i--)
	{
		node = player;
		for (int j = 0; j < i - 1; j++)
			node = node -> next;
		free(node);
	}
}

int	check_error(player_t *player, int n)
{
	player_t	*node;

	node = player;
	while (node -> next)
		node = node -> next;
	if (node -> no != n)
	{
		printf("Error\n");
		free_node(player);
		return (0);
	}
	return (1);
}

player_t	*create_players(player_t *player, int n)
{
	player_t	*node, *tmp;

	tmp = player;
	for (int i = 1; i <= n; i++)
	{
		tmp = (player_t *)malloc(sizeof(player_t));
		if (!tmp)
			break ;
		tmp -> next = NULL;
		tmp -> no = i;
		scanf("%d", &tmp -> shot);
		tmp -> status = 1;
		if (!player)
			player = tmp;
		else
		{
			node = player;
			while (node -> next)
				node = node -> next;
			node -> next = tmp;
		}
		if (tmp -> shot <= 0 || tmp -> shot > 100)
			break ;
	}
	return (player);
}

int	check_player(player_t *player)
{
	player_t	*node;
	int		count;

	node = player;
	count = 0;
	while (node)
	{
		if (node -> status)
			count++;
		node = node -> next;
	}
	if (count == 1)
		return (1);
	return (0);
}

int check_number(int count, int k)
{
	while (count)
	{
		if (count % 10 == k)
			return (1);
		count /= 10;
	}
	return (0);
}

int	countGame(player_t *player, int k)
{
	player_t	*node;
	int		count;

	node = player;
	count = 1;
	while (!check_player(player))
	{
		if (!node)
			node = player;
		else if (node -> status)
		{
			if (!(count % k) || check_number(count, k))
				node -> shot--;
			if (node -> shot < 0)
				node -> status--;
			//show_player(player, count);
			count++;
			node = node -> next;
		}
		else
			node = node -> next;
	}
	node = player;
	while (!node -> status)
		node = node -> next;
	return (node -> no);
}

int	main(void)
{
	player_t	*player;
	int		n, k;

	scanf("%d %d", &n, &k);
	if (n < 1 || n > 999999 || k < 1 || k > 9)
	{
		printf("Error\n");
		return (1);
	}
	player = NULL;
	player = create_players(player, n);
	if (!check_error(player, n))
		return (1);
	printf("%d\n", countGame(player, k));
	//show(player);
	free_node(player);
	return (0);
}
