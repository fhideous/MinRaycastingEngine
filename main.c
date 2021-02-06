#include <stdio.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"

struct n_map
{
	char			*line;
	struct n_map	*n;
} t_map;

void	*add_el(struct n_map *map, char **line)
{
	struct n_map *tmp;

	tmp = malloc(sizeof(char));
	map->n = tmp;
	tmp->line = *line;
	tmp->n = NULL;
	return (tmp);
}

/*
 * map parsing
 */

void *get_map(int fd)
{
	int		i;
 	struct n_map *map;
	char		*line;
	struct n_map *map_start;
	i = 0;
	map = ft_calloc(1 , sizeof(t_map));
	map->n = NULL;
	get_next_line(fd, &map->line);
	map_start = map;
	while (get_next_line(fd, &line))
	{
		map->n = add_el(map, &line);
		map = map->n;
	}
	return (map_start);
}

int main()
{
	int fd;
	struct n_map *map;

	fd = open("../map.noncub", O_RDONLY);
	if (fd <= 0)
		return (1);
	map = get_map(fd);

}
