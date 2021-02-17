#include <stdio.h>
#include <fcntl.h>
//#include "hdrs/get_next_line.h"
#include "hdrs/map_puuser.h"
#include "stdlib.h"
#include "lib/libft.h"


void del_f(void *ch)
{
	free(ch);
	ch = NULL;
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


/*
 * map parsing
 */

static char	**list_to_massive(t_list **hd, size_t len)
{
	char	  **map;
	int		  i;
	t_list	*tmp;
	t_list	*old;

	if (!(map = ft_calloc(len + 1, sizeof(char *))))
		return (NULL);
	tmp = *hd;
	i = -1;
	while (len--)
	{
		old = tmp;
		map[++i] = tmp->data;
		tmp = tmp->next;
		free(old);
	}
	return (map);
}

char		**get_map(char *path)
{
	char	*line;
	int		fd;
	t_list	*hd;
	char	**map;

	hd = NULL;
	line = NULL;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		ft_lstadd_back(&hd, ft_lstnew(line));
	ft_lstadd_back(&hd, ft_lstnew(line));
	map = list_to_massive(&hd, ft_lstsize(hd));
	return (map);
}
