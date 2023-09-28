#include <stdio.h>
#include <stdlib.h>

#define FOUND_ADDR	2
#define FOUND_DATA	1

typedef struct	cell
{
	int			data;
	int			mem_addr;
}				cell_t;

typedef struct	hash
{
	cell_t		*table;
	int			cache_size;
}				hash_t;

typedef hash_t	cache_t;
typedef int		memory_t;

memory_t *init_memory(int size)
{
	memory_t	*memory = (memory_t *)malloc(sizeof(memory_t) * size);
	int			i = 0;
	// Randomly assign integers to memory
	for (i = 0; i < size; i++)
		memory[i] = rand();
	return (memory);
}

cache_t	*init_cache(int size)
{
	cache_t	*cache;

	cache = malloc(sizeof(cache_t));
	if (!cache)
		return (NULL);
	cache -> table = calloc(sizeof(cell_t), size);
	if (!cache -> table)
	{
		free(cache);
		return (NULL);
	}
	cache -> cache_size = size;
	return (cache);
}

cell_t	*init_cell(int mem_addr, int data)
{
	cell_t	*cell;

	cell = malloc(sizeof(cell_t));
	if (!cell)
		return (NULL);
	cell -> data = data;
	cell -> mem_addr = mem_addr;
	return (cell);
}

unsigned int	cache_index(int mem_addr, int cache_size)
{
	return (mem_addr % cache_size);
}

int	search_cache(int mem_addr, cache_t *cache)
{
	unsigned int	index;

	if (!cache)
		return (0);
	index = cache_index(mem_addr, cache -> cache_size); 
	if (cache -> table[index].mem_addr != mem_addr)
	{
		if (cache -> table[index].data)
			return (FOUND_DATA);
		return (0);
	}
	return (FOUND_ADDR);
}

void	insert(int mem_addr, int data, cache_t *cache)
{
	unsigned int	index;
	cell_t			*cell;

	if (!cache)
		return ;
	index = cache_index(mem_addr, cache -> cache_size);
	cell = init_cell(mem_addr, data);
	if (!cell)
		return ;
	cache -> table[index] = *cell;
}

void	get_data(int mem_addr, memory_t *memory, cache_t *cache)
{
	unsigned int	index;

	if (!cache)
		return ;
	if (!search_cache(mem_addr, cache))
	{
		insert(mem_addr, memory[mem_addr], cache);
		printf("Load from memory\n");
		
	}
	else if (search_cache(mem_addr, cache) == FOUND_DATA)
	{
		index = cache_index(mem_addr, cache -> cache_size);
		insert(mem_addr, memory[mem_addr], cache);
		printf("Index: %u is used\n", index);
		printf("Load from memory\n");
	}
	else if (search_cache(mem_addr, cache) == FOUND_ADDR)
		printf("Address %d is loaded\n", mem_addr);
	printf("Data: %d\n", memory[mem_addr]);
}

int	main(void)
{
	memory_t	*memory = NULL;
	cache_t		*cache = NULL;
	int			memory_size, cache_size;
	int			i, n, addr;
	
	scanf("%d %d %d", &memory_size, &cache_size, &n);
	memory = init_memory(memory_size);
	cache = init_cache(cache_size);
	for (i = 0; i < n; i++)
	{
		printf("Load address: ");
		scanf("%d", &addr);
		get_data(addr, memory, cache);
	}
	return (0);
}