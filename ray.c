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

void find_crossing(t_all *all, float  angle, t_win *win)
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
//		my_mlx_pixel_put(win, (int)(end.x),
//						 (int)(end.y), 0xFF0000);
	}
	all->plr.ray.x = end.x + SCALE / 2;
	all->plr.ray.y = end.y + SCALE / 2;
	all->plr.ray.len = c;
//	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);

}

int		add_ver_line(int n, float len, int max_high, t_win *full_win) {
	int i;
	i = 0;
	while (i < (int)(len / 2)) {
		my_mlx_pixel_put(full_win, n,
						 i + (int)(max_high) / 2, 0xF0958659);
		i++;
	}
	i = 0;
	while (i != (int)(len /2)) {
		my_mlx_pixel_put(full_win, n,
						 (int)(max_high / 2) - i, 0xF0958659);
		i++;
	}

	mlx_put_image_to_window(full_win->mlx, full_win->win, full_win->img, 0, 0);
}


int		add_ray(t_all *all,const t_point *res)
{
	float	angle;
	float	high;
	int		n;

	n = 0;
	angle = -30;
	while (angle <= 30)
	{
		find_crossing(all, all->plr.ray.angle + angle / 57.2958,
					   all->full_win);
//		high = ABS (SCALE / all->plr.ray.len * res->x / 2 / tan(angle / 57.2958));
		add_ver_line(n, SCALE / all->plr.ray.len / 2 * res->y, res->y, all->full_win);
		angle += (float)60 / res->x;
		n++;
	}
}
