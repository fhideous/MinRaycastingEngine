//
// Created by fhideous on 15.04.2021.
//

#include "hdrs/cub3d.h"

int point_cmp(const t_point *point1, const t_point *point2)
{
	if(point1->x == point2->x && point2->y == point1->y)
		return 1;
	return 0;
}

int		add_dist_spr(t_sprites c)
;

int		add_point(t_point *massive, int x, int y)
{
	t_point tmp;
	t_point new_point;
	int		i;

	new_point.x = x;
	new_point.y = y;
	tmp.x = 0;
	tmp.y = 0;
	i = 0;
	while (!point_cmp(&massive[i], &tmp))
	{
		if (point_cmp(&massive[i], &new_point))
			break;
		i++;
	}
	if (!point_cmp(&massive[i], &tmp))
		return -1;
	else
	{
		massive[i] = new_point;
	}
	// to many sprites
	if (i >= SPRITES_MAX)
		return -19;
	return i;
}
