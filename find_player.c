
#include "hdrs/cub3d.h"
//#include "lib/libft.h"
//#include "hdrs/get_next_line.h"


int find_player(char **map, t_plr *player)
{
	int i;
	int j;
	double angle;

	i = 0;
	while((map[i]))
	{
		j = 0;
		while(map[i][j] && !ft_isalpha(map[i][j]))
			j++;
		if(ft_isalpha(map[i][j]))
			break ;
		i++;
	}
	angle = -1;
	player->x = (float)j;
	player->y = (float)i;
	if (map[i][j] == 'E')
		angle = 0;
	else if (map[i][j] == 'N')
		angle = M_PI / 2;
	else if (map[i][j] == 'W')
		angle = M_PI;
	else if (map[i][j] == 'S')
		angle = 3 * M_PI / 2;
	if (angle == -1)
		return (-1);
//	player->dir.x = player->x + STEP_X * cos(angle);
//	player->dir.y = player->y + STEP_Y * sin(angle);
	return(0);
}