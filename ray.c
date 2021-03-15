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

	c = (float)0.2;
	end.x = all->plr.x + c * cosf(angle);
	end.y  = all->plr.y + c * sinf(angle);
	while (all->full_map->map[(int)(end.y / SCALE)] [(int)(end.x / SCALE)] != '1')
	{
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)ANGLE_STEP;
//		my_mlx_pixel_put(win, (int)(end.x) / 4,
//						 (int)(end.y) / 4, 0xFF0000);
	}
	all->plr.ray.x = end.x + SCALE / 2;
	all->plr.ray.y = end.y + SCALE / 2;
	all->plr.ray.len = c;
//	mlx_put_image_to_window(win->mlx, win->win, win->img_tmp, 0, 0);

}

int		add_ver_line(int n, float len, int max_high, t_win *full_win) {
	int i;
	i = 0;

	while (i < (int)(len / 2)) {
		my_mlx_pixel_put(full_win, n,
						 i + (int)(max_high) / 2, 0x958659);
		i++;
	}
	i = 0;
	while (i != (int)(len /2)) {
		my_mlx_pixel_put(full_win, n,
						 (int)(max_high / 2) - i, 0x958659);
		i++;
	}
	mlx_put_image_to_window(full_win->mlx, full_win->win, full_win->img, 0, 0);
}

int		add_n_pixels(t_all *all, int n, int *w_it, int *txt_it)
{
	int i;

	i = -1;
	while (++i < n)
		all->full_win->addr[*w_it + i * all->full_map->resolution.x]
		= all->textrs.n_tex.addr[*txt_it];
*txt_it += SCALE;
}

int		add_texture_line(t_all *all, int n, float high, int dir)
{
	int i;
	unsigned  int *win_addr;
	unsigned int *txtr_addr;

//	txtr_addr = all->textrs.n_tex.addr;
//	win_addr = all->full_win->addr;
//	i = -1;
//	while (++i < high)
//		win_addr[n + ((i + all->full_map->resolution.y / 2 - (int)high/2) *
//		all->full_map->resolution.x )] =
//				txtr_addr[i * SCALE + (n % SCALE)];
	int w_it;
	int txt_it;
	i = 0;
	txt_it =  (n % SCALE) ;
	while (i < high)
	{
		w_it = n + ((i + all->full_map->resolution.y / 2 - (int)high/2) *
					all->full_map->resolution.x );
//		txt_it =(n % SCALE)  + i * SCALE ;
//		if (!(i % 32))

		if (!(i % 2))
			add_n_pixels(all,  high  / 4 ,&w_it, &txt_it);

		i += 1;
//		printf("%f\n", high);
	}
	mlx_put_image_to_window(all->full_win->mlx, all->full_win->win,
						 all->full_win->img, 0, 0);
}

int		add_ray(t_all *all,const t_point *res)
{
	float	angle;
	float	k;
	int		n;
	float high;

	n = 0;
	angle = -30;
//	ft_rotate(all->plr.ray, )
	while (angle <= 30)
	{
		k = cos(angle / 57.2958 );
		if (k == 0)
			k = 1;
		find_crossing(all, all->plr.ray.angle + angle / 57.2958,
					   all->full_win);
//		k = ABS (SCALE / all->plr.ray.len * res->x / 2 / tan(angle / 57.2958));
		angle += (float)60 / res->x;
		high = SCALE / all->plr.ray.len / 2 * res->y / k;
//		add_ver_line(n, high, res->y, all->full_win);
		add_texture_line(all, n, high, 0);
		n++;
	}
//	add_texture(all);
}
