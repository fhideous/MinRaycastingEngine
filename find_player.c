
#include "hdrs/cub3d.h"
//#include "lib/libft.h"
//#include "hdrs/get_next_line.h"


int find_player(char **map, t_plr *player, int scale)
{
	int i;
	int j;

	i = 0;
	while((map[i + 1]))
	{
		j = 0;
		while(map[i][j] && !ft_isalpha(map[i][j]/* && map[i][j] != '1' && map[i][j] != '2'*/))
			j++;
		if(ft_isalpha(map[i][j]))
			break ;
		i++;
	}
	player->ray.angle = -1;
	player->x = (float)j * (float)scale + (float)scale /2;
	player->y = (float)i * (float)scale + (float)scale /2;
	if (map[i][j] == 'E')
		player->ray.angle = 0;
	else if (map[i][j] == 'S')
		player->ray.angle = M_PI / 2;
	else if (map[i][j] == 'W')
		player->ray.angle = M_PI;
	else if (map[i][j] == 'N')
		player->ray.angle= 3 * M_PI / 2;
	if (player->ray.angle == -1)
		return (21);
	j++;
	while (map[i] && map[i][j])
	{
		while(map[i][j] && !ft_isalpha(map[i][j]))
			j++;
		if(ft_isalpha(map[i][j]))
			return (21);
		j = 0;
		i++;
	}
	player->ray.x = player->x + STEP_X * cosf(player->ray.angle);
	player->ray.y = player->y + STEP_Y * sinf(player->ray.angle);
	player->ray.len = 0.2;
	return(0);
}