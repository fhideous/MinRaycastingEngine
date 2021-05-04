#include "hdrs/cub3d.h"

float	ABS(float a)
{
	if (a < 0)
		return (-1 * a);
	return (a);
}

int	digits_in_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	dp_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

void	full_map_init(t_cub_map *full_map)
{
	full_map->res.x = 0;
	full_map->res.y = 0;
	full_map->fl_c.flag = 0;
	full_map->cl_c.flag = 0;
	full_map->map = NULL;
	full_map->n_t = NULL;
	full_map->e_t = NULL;
	full_map->s_t = NULL;
	full_map->w_t = NULL;
	full_map->s = NULL;
}

int	check_all_fields(t_cub_map *full_map)
{
	if (full_map->res.x == 0 || full_map->res.y == 0
		|| full_map->cl_c.flag == 0
		|| full_map->s == NULL || full_map->fl_c.flag == 0
		|| full_map->w_t == NULL
		|| full_map->s_t == NULL || full_map->e_t == NULL
		|| full_map->n_t == NULL || full_map->map == NULL)
		return (0);
	return (1);
}
