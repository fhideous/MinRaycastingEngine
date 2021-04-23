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

char		**get_map(int fd, char *line)
{
	t_list	*hd;
	char	**map;

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
	map = list_to_massive(&hd, ft_lstsize(hd));
	return (map);
}

int		count_sprites(char **map)
{
	int i;
	int j;
	int n;

	n = 0;
	i = 0;
	while (map[i][j])
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

int find_sprites(char **map, t_sprites_crds *sprts)
{
	int		i;
	int		j;
	int		cnt;
	t_point  point;

	sprts->n = 0;
	sprts->n = count_sprites(map);
	sprts->coordints = ft_calloc((sprts->n + 1), sizeof (t_point));
	i = 0;
	cnt = -1;
	j = 0;
	while (map[j])
	{
		j = 0;
		while(map[j] && map[j][i])
		{
			if (map[j][i] == '2')
			{
				point.x = j;
				point.y = i;
				sprts->coordints[++cnt] = point;
			}
			j++;
		}
		i++;
	}
}