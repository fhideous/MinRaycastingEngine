#include <stdio.h>
#include <fcntl.h>
//#include "hdrs/get_next_line.h"
#include "hdrs/map_puuser.h"
#include "stdlib.h"
#include "lib/libft.h"
#include "hdrs/cub3d.h"
//#include "lib/libft.h"

void del_f(void *ch)
{
	free(ch);
	ch = NULL;
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

/*
 * line приходит из parse_set
 */

int 		find_max(const char **map_old, int len)
{
	int i;
	int j;
	int max;

	i = 0;
	max = 0;
	while (i < len)
	{
		j = 0;
		while (map_old[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	if (i > max)
		max = i;
	return max;
}

char		**map_to_square(char **map_old, int len)
{
	char	**map_new;
	int 	len_max;
	int		i;
	int		j;

	len_max = find_max(map_old, len);
	map_new = ft_calloc(len_max + 1, sizeof(char*));
	i = -1;
	while (++i <= len_max)
		map_new[i] = ft_calloc(len_max + 1, sizeof(char));
	i = 0;
	while (i < len_max)
	{
		j = 0;
		while (j < len_max)
		{
			map_new[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	while(i < len)
	{
		j = 0;
		while (map_old[i][j])
		{
			map_new[i][j] = map_old[i][j];
			j++;
		}
		i++;
	}
	while (i--)
		free(map_old[i ]);
	free(map_old);
	return(map_new);
}

char		**get_map(int fd, char *line)
{
	t_list	*hd;
	char	**map;
	char	**square_map;
	int		n_lists;

	hd = NULL;
	if (line)
	{
		ft_lstadd_back(&hd, ft_lstnew(line));
		free(line);
	}
	while (get_next_line(fd, &line) == 1)
	{
		ft_lstadd_back(&hd, ft_lstnew(line));
		free(line);
	}
	ft_lstadd_back(&hd, ft_lstnew(line));
	free(line);
	n_lists =  ft_lstsize(hd);
	map = list_to_massive(&hd, n_lists);
	square_map = map_to_square(map, n_lists);
	return (square_map);
}

int		count_sprites(const char **map)
{
	int i;
	int j;
	int n;

	n = 0;
	i = 0;
	while (i < (int)ft_strlen(map[0]))
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == '2')
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

int find_sprites(const char **map, t_all *all)
{
	int		i;
	int		j;
	int		cnt;
	t_point  point;

	all->size_sprites =count_sprites(map);
	all->sprites_loc = ft_calloc((all->size_sprites + 1), sizeof(t_sprite));
	cnt = -1;
	j = 0;
	while (map[j] && map[j][0])
	{
		i = 0;
		while(map[j] && map[j][i])
		{
			if (map[j][i] == '2')
			{
				point.x = j;
				point.y = i;
				all->sprites_loc[++cnt].coords = point;
			}
			i++;
		}
		j++;
	}
	return 0;
}