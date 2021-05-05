#include "hdrs/cub3d.h"

void	player_cast(char **map, float *angle, int i, int j)
{
	if (map[i][j] == 'E')
		*angle = 0;
	else if (map[i][j] == 'S')
		*angle = M_PI / 2;
	else if (map[i][j] == 'W')
		*angle = M_PI;
	else if (map[i][j] == 'N')
		*angle = 3 * M_PI / 2;
}

void	skip_to_plr(char **map, int *i, int *j)
{
	while ((map[*i + 1]))
	{
		*j = 0;
		while (map[*i][*j] && !ft_isalpha(map[*i][*j]))
			(*j)++;
		if (ft_isalpha(map[*i][*j]))
			break ;
		(*i)++;
	}
}

int	find_player(char **map, t_plr *player, int scale)
{
	int	i;
	int	j;

	i = 0;
	skip_to_plr(map, &i, &j);
	player->ray.angle = -1;
	player->x = (float)j * (float)scale + (float)scale /2;
	player->y = (float)i * (float)scale + (float)scale /2;
	player_cast(map, &player->ray.angle, i, j);
	if (player->ray.angle == -1)
		return (19);
	j++;
	while (map[i] && map[i][j])
	{
		while (map[i][j] && !ft_isalpha(map[i][j]))
			j++;
		if (ft_isalpha(map[i][j]))
			return (19);
		j = 0;
		i++;
	}
	player->ray.x = player->x + STEP_X * cosf(player->ray.angle);
	player->ray.y = player->y + STEP_Y * sinf(player->ray.angle);
	player->ray.len = 0.2;
	return (0);
}
