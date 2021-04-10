#include "hdrs/cub3d.h"
#include <math.h>

void            my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


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

void	add_sprite_line(t_all *all, int n, int high)
{
	int		j;
	int					k;
	float 				ratio;
	int					i;

	i = (int)all->plr.ray.x % all->textrs.spite.width;
	ratio = (float)high / all->textrs.spite.width;
	j = -ratio;
	while(j < high)
	{
		k = 0;
		j += ratio;
		if (all->textrs.spite.addr[(int) ((j * all->textrs.spite.width / ratio) + i )] == 0x000000)
			continue;
		while (k < ratio)
		{
			all->full_win->addr[(int)(k + j) * all->full_map->resolution.x + n +
								all->full_map->resolution.x *
								((all->full_map->resolution.y >> 1) - (int)(high >> 1))]  =
					all->textrs.spite.addr[(int) ((j * all->textrs.spite.width / ratio) + i )];
			k++;
		}
	}
}

int		add_sprite(t_all *all, t_sprite sprite, int scale)
{
	int		i;
	float 	high;
	int		n;
	int		n_end;

	i = -1;
	while(i++ != all->sprts_crds.n)
	{
		if (all->spr_distans[i].angle > all->plr.ray.angle - M_PI_6 * 2 &&
				(all->spr_distans[i].angle < all->plr.ray.angle + M_PI_6 * 2))
		{
			n = all->full_map->resolution.x / 2 +
					all->plr.ray.angle * all->full_map->resolution.x;
			high = sprite.width / all->spr_distans[i].dist * all->full_map->resolution.y ;
			n_end = n + all->textrs.spite.width;
			while (n < n_end)
			{
//				add_sprite_line(all, n, high);
				n++;
			}
		}
	}
}

void		distance_sprites(const t_sprites_crds *crds,
					   const t_plr* plr,
					   t_sprites_distns *distns)
{
	int		i;
	float	x;
	float	y;
	i = -1;
	while (++i < crds->n)
	{
		x = (crds->coordints[i].x - plr->x);
		y = (crds->coordints[i].y - plr->y);
		distns[i].dist =  sqrt(x * x + y * y);
		distns[i].angle = atanf(y / x);
	}
}


int     render_next_frame(t_all *all)
{
	add_flour(all);

	add_ray(all, &all->full_map->resolution, (float)all->full_map->resolution.x / all->full_map->resolution.y );
	all->textrs.spite.angle = 0;
	all->textrs.spite.k = 1;
	distance_sprites(&all->sprts_crds, &all->plr, all->spr_distans);
	add_sprite(all, all->textrs.spite, all->textrs.n_tex.width);
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