//
// Created by fhideous on 08.03.2021.
//
#include "hdrs/cub3d.h"

void print_ray(t_win *win, t_ray *start, t_ray *end, float angle)
{
	t_ray *ray;
	float c;

	c = 0.1;
	ray = start;
	while (c <= end->len)
	{
		my_mlx_pixel_put(win, (int)(ray->x),
				   (int)(ray->y), 0xFF0000);
		start->len += c;
		ray->x = start->x + c * cos(angle) ;
		ray->y = start->y + c * sin(angle) ;
		c += 0.2;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
}