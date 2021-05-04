#include "hdrs/cub3d.h"

int	check_opposite_sign(const char **map, int i, int j, int sign)
{
	if (map[i][j + sign] == '\0' || map[i][j + sign] == ' ')
		return (-1);
	if (map[i + sign][j] == '\0' || map[i + sign][j] == ' ')
		return (-1);
	if (map[i + sign][j + sign] == '\0' || map[i + sign][j + sign] == ' ')
		return (-1);
	if (map[i - sign][j + sign] == '\0' || map[i - sign][j + sign] == ' ')
		return (-1);
	return (0);
}

int	check_opposite(const char **map, int i, int j)
{
	int	flag;

	flag = check_opposite_sign(map, j, i, 1);
	flag += check_opposite_sign(map, j, i, -1);
	if (flag != 0)
		return (-1);
	return (0);
}

int	check_first_hv_line(const char **map, size_t ij_max)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (j < ij_max)
	{
		if (map[j][0] != '1' && map[j][0] != ' ')
			return (18);
		j++;
	}
	while (i < ij_max)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			return (18);
		i++;
	}
	return (0);
}

int	check_last_hv_line(const char **map, size_t ij_max)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (j < ij_max)
	{
		while (i < ij_max)
			i++;
		if (map[j][i - 1] != '1' && map[j][i - 1] != ' ')
			return (18);
		j++;
		i = 0;
	}
	return (0);
}

int	map_validate(const char **map)
{
	int			i;
	int			j;
	size_t		ij_max;

	if (!map)
		return (18);
	ij_max = ft_strlen(map[0]);
	if (check_first_hv_line(map, ij_max))
		return (18);
	if (check_last_hv_line(map, ij_max))
		return (18);
	j = 1;
	while (j < ij_max)
	{
		i = 1;
		while (i < ij_max)
		{
			if (map[j][i] == '0')
				if (check_opposite(map, i, j) == -1)
					return (18);
			i++;
		}
		j++;
	}
	return (0);
}
