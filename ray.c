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

t_texture texture_define(t_ray *ray_new, t_textures *all_txtr, int *is_x)
{
	static t_ray ray_old;
	t_texture	tmp_txtr;
	float		x_delt;
	float		y_delt;

	x_delt = ray_new->x - ray_old.x;
	y_delt = ray_new->y - ray_old.y;
	if(ABS(x_delt) > ABS(y_delt) && x_delt > 0)
	{
		tmp_txtr = all_txtr->s_tex;
		*is_x = 1;
	}
	else if (ABS(y_delt) > ABS(x_delt) && y_delt > 0)
		tmp_txtr = all_txtr->e_tex;
	else if (ABS(x_delt) > ABS(y_delt) && x_delt < 0)
	{
		tmp_txtr = all_txtr->n_tex;
		*is_x = 1;
	}
	else
		tmp_txtr = all_txtr->w_tex;
	ray_old = *ray_new;
	return tmp_txtr;
}

void	add_scale_line(t_all *all, int n, int hign, t_texture *textr, int is_x)
{
	int i ;
	float ratio = (float)hign / SCALE;
	float k = 0;
	float j = 0;
	if(is_x)
		i = (int)all->plr.ray.x % SCALE;
	else
		i = (int)all->plr.ray.y % SCALE;
	float j_rat = (float)ratio * SCALE;

	int cnt = 0;
//	while (cnt < SCALE)
//	{
	j = 0;
	while (j < j_rat )
	{
		k = 0;
		while (k < ratio)
		{
			all->full_win->addr[(int)(k + j) * all->full_map->resolution.x + cnt + n +
								all->full_map->resolution.x *
								((all->full_map->resolution.y >> 1) - (hign >> 1)) ]  =
					textr->addr[(int) (j * SCALE / ratio) + i];
			k++;
		}
		j += (ratio);
	}
	i++;
	cnt++;
//	}


}

int		add_ray(t_all *all,const t_point *res)
{
	float	angle;
	float	k;
	int		n;
	float high;
	t_texture texture;
	int 	is_x;

	n = 0;
	angle = M_PI_6_N;
	while (n < res->x)
	{
		is_x = 0;
		k = cos(angle);
		if (k == 0)
			k = 1;
		find_crossing(all, all->plr.ray.angle + angle,
					   all->full_win);
		high = SCALE / all->plr.ray.len * res->y / k * 1.2;
		texture = texture_define(&all->plr.ray, &all->textrs, &is_x);
		add_scale_line(all, n, (int)(high), &texture, is_x);
		n += 1;
		angle += 1.0 /res->x ;
	}
//	add_texture(all);
}
