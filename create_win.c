#include "hdrs/cub3d.h"
#include <math.h>

void add_flour(t_all *all)
{
	int i;
	int j;

	j = (all->full_map->resolution.y >> 1) * all->full_map->resolution.x;
	 i = j;
	while (i--)
			all->full_win->addr[i] = 0xE3CC87;
	i = -1;
	while (++i != j)
		all->full_win->addr[i + j] = 0xE3D29F;
	mlx_put_image_to_window(all->full_win->mlx, all->full_win->win, all->full_win->img, 0, 0);

}

void	print_sprite_line(const t_all *all,int n, int high, int it)
{
	float		ratio;
	int			i;
	float		j;
	int			k;

	ratio = (float)high / (float)all->textrs.spite.width;
	i = ((int)all->sprites_loc.coords->y - (all->textrs.spite.width >> 1)) % all->textrs.spite.width;
	j = 0;
	while (j < (float)high)
	{
		k = 0;
		while ((float)k < ratio)
		{
			if(((k + (int)j + (all->full_map->resolution.y >> 1) >= (high >> 1))) &&
			   (k + (int)j < (high >> 1) + (all->full_map->resolution.y >> 1))) {
				all->full_win->addr[(k + (int) j) * all->full_map->resolution.x + n +
									all->full_map->resolution.x *
									((all->full_map->resolution.y >> 1) - (int) (high >> 1))] =
						all->textrs.spite.addr[(((int) all->textrs.spite.width * (int) (j / ratio)) + i + it)];
				k++;
			}
		}
		j += ratio;
	}
}

void	sprite_sort()
{

}

int		crossing_sprite(const t_all *all, float angle, const t_texture *txtr)
{
	t_ray	end;
	float	c;
	char	ch;

	c = (float)LEN_STEP;
	end.x = all->plr.x + c * cosf(angle);
	end.y = all->plr.y + c * sinf(angle);
	ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
		 [(int)(end.x / (float)txtr->width)];
	while (ch != '1')
	{
		if (ch == '2')
			return 1;
		ch = all->full_map->map[(int)(end.y / (float)txtr->width)]
			[(int)(end.x / (float)txtr->width)];
		end.x = all->plr.x + c * cosf(angle);
		end.y  = all->plr.y + c * sinf(angle);
		c += (float)LEN_STEP;
	}
	return  0;
}

int		curr_sprite_width(const t_all *all, float angle, int high)
{
	int		curr;
	float	left;
	float	right;
	float	high_angle;
	float	eps;

	left = 0;
	eps	= (float)(M_PI_6 + M_PI_6) / (float)all->full_map->resolution.x;
	high_angle = (float)high * eps;
	right = ABS(high_angle);
	angle += (high_angle / 2);
	curr = crossing_sprite(all, angle, &all->textrs.n_tex);
	while ((right - left) > eps)
	{
		if (curr == 1)
		{
			left += (right - left) / 2;
			angle += (right - left) / 2;
		}
		else
		{
			right -= (right - left) / 2;
			angle -= (right - left) / 2;
		}
		curr = crossing_sprite(all, angle, &all->textrs.n_tex);
	}
	return ABS((int)((left) / (float)(M_PI_6 + M_PI_6) * (float)all->full_map->resolution.x));
}

int		add_sprite(const t_all *all, const t_sprites *sprite_data, float x_y) {
	int i;
	int n;
	float j;
	int high;
	float angle;
	int width;
	i = 0;
	j = 0;
	while (i <= sprite_data->size) {

		angle = sprite_data->distns[i].angle - all->plr.ray.angle;
		high = (int)(x_y * all->full_map->resolution.y * all->textrs.spite.width / sprite_data->distns[i].dist);
		if (high > all->full_map->resolution.y )
			high = all->full_map->resolution.y;

		n = all->full_map->resolution.x / 2 * (1 + ( angle / ( M_PI_6)));

		float sp_step_step = 0;
		width = curr_sprite_width(all, (sprite_data->distns[i].angle), high);
		printf("%d\n", width);
		float sp_step = (float)width / all->textrs.spite.width;
		int kek = 0;
		while ((int)j < width && j + n < all->full_map->resolution.x)
		{
			sp_step_step = 0;
			while (sp_step_step < sp_step)
			{
				print_sprite_line(all, n + sp_step_step + j, high,  kek);
				sp_step_step++;
			}
			kek ++;
			j += sp_step;
		}

		i++;
		j = 0;
	}
}

int     render_next_frame(t_all *all)
{
	add_flour(all);

	sprites_zero(all->sprites_loc.points);
	sprites_dist_sero(all->sprites_loc.distns);
	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y );
//	all->textrs.spite.angle = 0;
//	all->textrs.spite.k = 1;

//	distance_sprites(&all->sprts_crds, &all->plr, all->spr_distans,all->textrs.n_tex.width );
//	add_sprite(all, all->textrs.spite, all->textrs.n_tex.width);
	sprite_sort();
	add_sprite(all, &all->sprites_loc, (float)all->full_map->resolution.x / all->full_map->resolution.y );
}


int	create_win(t_all *all)
{
//	t_win 	*win;

//	win = malloc(sizeof(t_win));
	all->full_win->win = mlx_new_window(all->full_win->mlx, all->full_map->resolution.x,
								  all->full_map->resolution.y, "cub3d");

	all->full_win->img = mlx_new_image(all->full_win->mlx, all->full_map->resolution.x,
							 all->full_map->resolution.y);
	all->full_win->addr = mlx_get_data_addr(all->full_win->img,
								  &all->full_win->bits_per_pixel,
								  &all->full_win->line_length,
								  &all->full_win->endian);
//	all->full_win = win;
//	render_next_frame(&all, &full_map);
	mlx_loop_hook(all->full_win->mlx, render_next_frame, &all->full_win);

	mlx_hook(all->full_win->win, 2, 1L << 0, key_commands, all);
//	render_next_frame(&all);

	mlx_loop(all->full_win->mlx);
}