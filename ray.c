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

//void	find_y_crossing(t_ray *ray,const t_all *all, float angle)
//{
//	int		up_o_d;
//	float 	x_step;
//
//	up_o_d = 1;
//	if (all->plr.y < ray->y)
//		up_o_d = -1;
//	ray->len = STEP_Y * up_o_d;
//	while (ABS(all->plr.y - ray->y) < 1)
//	{
//		ray->y = all->plr.y + ray->len * sin(angle);
//		ray->len += STEP_Y ;
//	}
//	printf("new square y: %f\n", ray->y);
//	x_step = 1 / tan(angle * (-1) * up_o_d);
//	printf("x_step: %f\n", x_step);
//	while (all->map[(int)ray->y - 1][(int)ray->x - 1] != '1')
//	{
//		ray->y += 1;
//		ray->x += up_o_d * x_step;
//	}
//	printf("wall detect_y:  %f; %f , len = %f \n\n", ray->x, ray->y, ray->len);
//}
//
//t_ray	find_y_crossing(const t_all *all, float angle)
//{
//	t_ray r_end;
//	int		is_down;
//	float x_step;
//	float y_step;
//
//	is_down = 1;
//	//ray cast down
//	if (all->plr.y > all->plr.ray.y)
//		r_end.y = (int)(all->plr.y / SCALE) * SCALE + SCALE;
//	else
//	{//ray cast up
//		is_down = -1;
//		r_end.y = (int)(all->plr.y / SCALE) * SCALE - 1;
//	}
//	r_end.x = all->plr.x + (all->plr.y - r_end.y) / tan(angle);
//	y_step = SCALE * is_down;
//	x_step = SCALE / tan(angle);
//	while(all->map[(int)(r_end.y / SCALE - 1)][(int)(r_end.x / SCALE)] != '1')
//	{
//		r_end.x += x_step;
//		r_end.y += y_step;
//	}
//	r_end.len = ABS( (all->plr.y - r_end.y) / sin (angle) );
//	return (r_end);
//}
//
//t_ray	find_x_crossing(const t_all *all, float angle)
//{
//	t_ray r_end;
//	int		is_right;
//	float x_step;
//	float y_step;
//
//	is_right = 1;
//	//ray cast right
//	if (all->plr.x > all->plr.ray.x)
//		r_end.x = (int)(all->plr.x / SCALE) * SCALE + SCALE;
//	else
//	{//ray cast up
//		is_right = -1;
//		r_end.x = (int)(all->plr.x / SCALE) * SCALE - 1;
//	}
//	r_end.x = all->plr.x + (all->plr.y - r_end.y) / tan(angle);
//	x_step = SCALE * is_right;
//	y_step = SCALE * tan(angle);
//	while(all->map[(int)(r_end.y / SCALE - 1)][(int)(r_end.x / SCALE)] != '1')
//	{
//		r_end.x += x_step;
//		r_end.y += y_step;
//	}
//	r_end.len = ABS( (all->plr.y - r_end.y) / sin (angle) );
//	return (r_end);
//}

t_ray find_crossing(t_all *all, float  angle, t_win *win)
{
	t_ray end;
	float  c;

	c = 0.2;
	end.x = all->plr.x + c * cos(angle);
	end.y  = all->plr.y + c * sin(angle);
	while (all->map[(int)(end.y / SCALE)] [(int)(end.x / SCALE)] != '1')
	{
		end.x = all->plr.x + c * cos(angle);
		end.y  = all->plr.y + c * sin(angle);
		c += 0.2;
		my_mlx_pixel_put(win, (int)(end.x),
						 (int)(end.y), 0xFF0000);
	}
	all->plr.ray.x = end.x + SCALE / 2;
	all->plr.ray.y = end.y + SCALE / 2;
	all->plr.ray.len = c;
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);

}

int		add_ray(t_all *all)
{
	t_ray ray_start;
	t_ray *ray;
	float	angle;

	angle = -30;
	ray = &all->plr.ray;
	ray_start.x = all->plr.x + SCALE / 2;
	ray_start.y = all->plr.y + SCALE / 2;
//	printf("old: %f;%f\n", ray->x, ray->y);
//	ft_rotate(ray, &ray_start, angle);
//	printf("new: %f;%f\n", ray->x, ray->y);
	while (angle <= 30)
	{
	find_crossing(all, all->plr.ray.angle + angle / 57.2958,
			   all->full_win);
	ray_start.len = 0;
//	print_ray(all->full_win, ray_start, all->plr.ray, angle / 57.2958);
	angle += 1;

	}
}
