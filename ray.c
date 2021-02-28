#include "hdrs/cub3d.h"

void		ft_rotate(t_ray *ray, t_ray *start, float angle)
{
	float	angle_rad;
	float	x;

	x = ray->x;
	angle_rad = angle / 57.2958;
	x = start->x + (ray->x - start->x) * cos(angle_rad) -
			(ray->y - start->y) * sin(angle_rad);
	ray->y = start->y + (ray->x - start->x) * sin(angle_rad) +
			 (ray->y - start->y) * cos(angle_rad);
	ray->x = x;
}

int		add_ray(t_all *all)
{
	t_ray ray_start;
	t_ray *ray;

	ray = &all->plr.ray;
	ray_start.x = all->plr.x;
	ray_start.y = all->plr.y;
	printf("old: %f;%f\n", ray->x, ray->y);
	ft_rotate(ray, &ray_start, 90);
	printf("new: %f;%f\n", ray->x, ray->y);

}

