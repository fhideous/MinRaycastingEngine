#include "hdrs/cub3d.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))

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

void	find_y_crossing(t_ray *ray,const t_all *all, float angle)
{
	int		up_o_d;
	float 	x_step;

	up_o_d = 1;
	if (all->plr.y < ray->y)
		up_o_d = -1;
	ray->len = STEP_Y * up_o_d;
	while (ABS(all->plr.y - ray->y) < 1)
	{
		ray->y = all->plr.y + ray->len * sin(angle);
		ray->len += STEP_Y ;
	}
	printf("new square y: %f\n", ray->y);
	x_step = 1 / tan(angle * (-1) * up_o_d);
	printf("x_step: %f\n", x_step);
	while (all->map[(int)ray->y - 1][(int)ray->x - 1] != '1')
	{
		ray->y += 1;
		ray->x += up_o_d * x_step;
	}
	printf("wall detect_y:  %f; %f , len = %f \n\n", ray->x, ray->y, ray->len);
}

int		add_ray(t_all *all)
{
	t_ray ray_start;
	t_ray *ray;
	float	angle;

	angle = 90;
	ray = &all->plr.ray;
	ray_start.x = all->plr.x;
	ray_start.y = all->plr.y;
	printf("old: %f;%f\n", ray->x, ray->y);
	ft_rotate(ray, &ray_start, angle);
	printf("new: %f;%f\n", ray->x, ray->y);
//	while (angle < 60)
//	{
		find_y_crossing(ray, all, angle / 57.2958);
		angle += 0.2;
//	}
}
