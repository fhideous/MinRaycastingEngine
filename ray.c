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

int		add_n_pixels(t_all *all, int n, int w_it, int *txt_it)
{
	int i;

	i = -1;
	while (++i < n)
		all->full_win->addr[w_it + i * all->full_map->resolution.x] =
				all->textrs.n_tex.addr[*txt_it];
	*txt_it += SCALE;
}

int		add_texture_line(t_all *all, int n, float high, int dir)
{
	float i;
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
	while (i < (int)high)
	{

//		w_it = n + ((i + (all->full_map->resolution.y >> 1) - ((int)high >> 1)) *
//					all->full_map->resolution.x );
		w_it = n + i * all->full_map->resolution.x + all->full_map->resolution.x *
				((all->full_map->resolution.y >> 1) - ((int)high >> 1));
//		if (!(i % 2))
//		add_n_pixels(all,  ((int)high % 32) ,w_it, &txt_it);
		int j = 0;
		while (j <= (int) high)
		{
			all->full_win->addr[(int)(w_it + (i + j) * all->full_map->resolution.x)] =
					all->textrs.n_tex.addr[txt_it];
			j++;
		}
		txt_it += SCALE;
		if(txt_it > 1024)
			break;
		i += (1);
	}


//	int text_size = 32;
//	float step;
//	float count;
//	int win_pixl;
//
//	count = 0;
//	while (count < high)
//	{
//		step = high / text_size;
//		win_pixl = n + (all->full_map->resolution.x *
//				((all->full_map->resolution.y >> 1) - ((int)high >> 1)));
//		while (step > 1) {
//			all->full_win->addr[(int)(win_pixl + (count + step) * all->full_map->resolution.x)] =
//					all->full_map->n_texture[n % text_size +
//											 text_size * ((int) (count + step) % text_size)];
//			step--;
//		}
//		count += step;
//	}



//	mlx_put_image_to_window(all->full_win->mlx, all->full_win->win,
//						 all->full_win->img, 0, 20);
}

void	add_scale_line(t_all *all, int n, int hign, t_texture *textr)
{
	int HIGH =  hign;
	int i = 0;
	float ratio = (float)HIGH / SCALE;
	float k = 0;
	float j = 0;
	i = n % SCALE;
	float j_rat = (float)ratio * SCALE;
//	while (i < SCALE)
//	{
		j = 0;
		while (j < j_rat)
		{
			k = 0;
			while (k < ratio)
			{
				all->full_win->addr[(int)(k + j) * all->full_map->resolution.x + n +
						all->full_map->resolution.x *
								((all->full_map->resolution.y >> 1) - (hign >> 1)) ]  =
					textr->addr[(int) (j * SCALE / ratio) + i];
				k++;
			}
			j += ratio;
		}
		i++;
//	}


}

t_texture texture_define(t_ray *ray_new, t_textures *all_txtr)
{
	static t_ray ray_old;
	t_texture	tmp_txtr;
	float		x_delt;
	float		y_delt;

	if (ray_old.len == 0)
	{
		ray_old = *ray_new;
		return all_txtr->n_tex;
	}
	x_delt = ray_new->x - ray_old.x;
	y_delt = ray_new->y - ray_old.y;
	if(ABS(x_delt) > ABS(y_delt) && x_delt > 0)
		tmp_txtr = all_txtr->s_tex;
	else if (ABS(y_delt) > ABS(x_delt) && y_delt > 0)
		tmp_txtr = all_txtr->e_tex;
	else if (ABS(x_delt) > ABS(y_delt) && x_delt < 0)
		tmp_txtr = all_txtr->n_tex;
	else
		tmp_txtr = all_txtr->w_tex;
	ray_old = *ray_new;
	return tmp_txtr;
}

int		add_ray(t_all *all,const t_point *res)
{
	float	angle;
	float	k;
	int		n;
	float high;
	t_texture texture;

	n = 0;
	angle = M_PI_6_N;
	while (n < res->x)
	{
		k = cos(angle);
		if (k == 0)
			k = 1;
		find_crossing(all, all->plr.ray.angle + angle,
					   all->full_win);
		///&&&&&&&????????
		angle += 1.0 /res->x ;
		high = SCALE / all->plr.ray.len / 2 * res->y / k;
//		add_texture_line(all, n, (int)high, 0);

		texture = texture_define(&all->plr.ray, &all->textrs);
		add_scale_line(all,n, (int)(high), &texture);
		n += 1;
	}
//	add_texture(all);
}
