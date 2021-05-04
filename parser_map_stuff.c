#include "hdrs/cub3d.h"

int	count_sprites (const char **map)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = 0;
	while (i < ft_strlen(map[0]))
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

int	find_sprites (const char **map, t_all *all)
{
	int		i;
	int		j;
	int		cnt;
	t_point	point;

	all->s_spr =count_sprites(map);
	all->spr_loc = ft_calloc((all->s_spr + 1), sizeof(t_sprite));
	cnt = -1;
	j = 0;
	while (map[j] && map[j][0])
	{
		i = 0;
		while (map[j] && map[j][i])
		{
			if (map[j][i] == '2')
			{
				point.x = j;
				point.y = i;
				all->spr_loc[++cnt].coords = point;
			}
			i++;
		}
		j++;
	}
	return (0);
}

int	find_max(char **map_old, int len)
{
	int		i;
	int		j;
	int		max;

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
	return (max);
}
