#include "hdrs/cub3d.h"
#include <math.h>

//void            my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color)
//{
//	char    *dst;
//
//	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//	*(unsigned int*)dst = color;
//}


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

void	add_sprite_line(t_all *all, int n, int high, int i)
{
	float				j;
	int					k;
	float 				ratio;
//	int					i;
//	i = 0;
//	i = ((int)all->plr.ray.y - 32) % all->textrs.spite.width;
	if (high > all->full_map->resolution.y )
		high = all->full_map->resolution.y ;
	ratio = (float)high / all->textrs.spite.width;
	j = -ratio;
	while(j + ratio < high)
	{
		k = 0;
		j += ratio;
		if (all->textrs.spite.addr[(((int)(j / ratio) * all->textrs.spite.width) + i )] == 0x000000)
			continue;
		while (k < ratio)
		{
			all->full_win->addr[(k + (int)j) * all->full_map->resolution.x + n +
								all->full_map->resolution.x *
								((all->full_map->resolution.y >> 1) - (int)(high >> 1))]  =
					all->textrs.spite.addr[(((int)(j / ratio ) * all->textrs.spite.width) +
						i)];
			k++;
		}
	}
}

/*int		add_sprite(t_all *all, t_sprite sprite, int scale)
{
	int		i;
	int 	high;
	int		n;
	int		n_end;
	float	step;
	int		it_step;
	int		k;
	i = -1;
	while(++i != all->sprts_crds.n)
	{
		if (all->spr_distans[i].angle > M_PI_2  - M_PI_6 &&
				(all->spr_distans[i].angle < M_PI_2 + M_PI_6))
		{
			n = all->sprts_crds.coordints->x + ((int)(all->spr_distans[i].dist * cosf(all->spr_distans[i].angle)));
			high = (int)(sprite.width / all->spr_distans[i].dist * all->full_map->resolution.y) >> 1;
			n_end = n + *//*all->textrs.spite.width / all->full_map->resolution.x*//*
					high;
			step = (float)high / (float)sprite.width;
			it_step = 0;
			k = 0;
			while (n <= n_end)
			{
				add_sprite_line(all, n, high, k);
				it_step++;
				if ((float)it_step >= step)
				{
					it_step = 0;
					k++;
				}
				n++;
			}
		}
	}
}*/

/*
void		distance_sprites(const t_sprites_crds *crds,
					   const t_plr* plr,
					   t_sprites_distns *distns, int scale)
{
	int		i;
	float	x;
	float	y;
	i = -1;
	while (++i < crds->n)
	{
		x = (crds->coordints[i].x - plr->x);
		y = (crds->coordints[i].y - (plr->y - (scale >> 1)));
		distns[i].dist =  sqrt(x * x + y * y);
		distns[i].angle = asinf(ABS(x) / distns[i].dist);
	}
}
*/

void	sprite_sort()
{

}

int		add_sprite(const t_all *all, const t_sprites sprite_data, float x_y) {
	int i;
	int n;
	int j;
	int k;
	int high;
	float angle;

	i = 0;
	j = 0;
	while (i <= sprite_data.size) {
//		n = ((int)(sprite_data.distns[i].dist * cosf(sprite_data.distns[i].angle)));
//		high = (int)(all->textrs.spite.width / sprite_data.distns[i].dist * all->full_map->resolution.y) >> 1;
//		high = (all->full_map->resolution.y * all->textrs.spite.width / sprite_data.distns[i].dist);
//		if (high > all->full_map->resolution.y ) {
//			high = all->full_map->resolution.y ;
//		}
//		n = sprite_data.coords->y + high;
		angle = sprite_data.distns[i].angle - all->plr.ray.angle;
		high = (int)(x_y * all->full_map->resolution.y * all->textrs.spite.width / sprite_data.distns[i].dist);
		if (high > all->full_map->resolution.y )
			high = all->full_map->resolution.y;
//		n =  sprite_data.points->y;
//		n = (all->full_map->resolution.x -
//				(int)(2 * sprite_data.distns[i].dist * (cosf(sprite_data.distns[i].angle)))) / 2;
		n = all->full_map->resolution.x / 2 * (1 + ( angle / ( M_PI_6)));
		while (j < high && j + n < all->full_map->resolution.x)
		{
			add_scale_line(all, n + j, high, &all->textrs.spite, 0);
			j++;
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
	add_sprite(all, all->sprites_loc, (float)all->full_map->resolution.x / all->full_map->resolution.y );
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