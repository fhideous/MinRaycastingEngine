#include <stdio.h>
#include <fcntl.h>
//#include "hdrs/get_next_line.h"
#include "hdrs/map_puuser.h"
#include "stdlib.h"
#include "lib/libft.h"


void	*add_el(struct n_map *map, char **line)
{
	struct n_map *tmp;

	tmp = malloc(sizeof(t_map));
	map->n = tmp;
	tmp->line = *line;
	tmp->n = NULL;
	return (tmp);
}

void list_free(struct n_map **map)
{
	struct n_map* cur = *map;
	struct n_map* next;

	while (cur != NULL)
	{
		next = cur->n;
		free(cur->line);
		free(cur);
		cur = next;
	}
	*map = NULL;
}

int map_struct_strs(struct n_map *map, char ***strs, int size)
{
	int line_l;

	if(!(strs = ft_calloc(size + 1, sizeof(char*))))
		return (-1);
	while (map)
	{
		line_l = ft_strlen(map->line);
		if(!(**strs = ft_calloc(line_l + 1, sizeof(char))))
			return (-1);
		ft_memcpy(**strs, map->line, line_l);
		map = map->n;
	}
	return (0);
}

int list_size(struct n_map *map)
{
	size_t	i;

	i = 0;
	while(map)
	{
		i++;
		map = map->n;
	}
	return (i);
}

/*
 * map parsing
 */

void *get_map(int fd)
{
 	struct n_map *map;
	char		*line;
	struct n_map *map_start;
	char		**map_strs;

	map = ft_calloc(1 , sizeof(struct n_map));
	map_start = map;
	map->n = NULL;
	get_next_line(fd, &map->line);
	while (get_next_line(fd, &line))
	{
		map->n = add_el(map, &line);
		map = map->n;
	}
	map->n = add_el(map, &line);
	map = map->n;
	if((map_struct_strs(map_start, &map_strs, list_size(map_start))) == -1)
		return(NULL);

	list_free(&map_start);
	return (map_strs);
}
