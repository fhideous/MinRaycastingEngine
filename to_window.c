#include "hdrs/cub3d.h"

void	add_flour(t_all *all)
{
	int				i;
	int				j;
	unsigned int	color_f;
	unsigned int	color_c;

	color_f = (all->f_map->fl_c.R << 16)
		+ (all->f_map->fl_c.G << 8) + all->f_map->fl_c.B;
	color_c = (all->f_map->cl_c.R << 16)
		 + (all->f_map->cl_c.G << 8) + all->f_map->cl_c.B;
	j = (all->f_map->res.y >> 1) * all->f_map->res.x;
	i = j;
	while (i--)
		all->f_w.addr[i] =color_c;
	i = -1;
	while (++i != j)
		all->f_w.addr[i + j] = color_f;
	mlx_put_image_to_window(all->f_w.mlx, all->f_w.win, all->f_w.img, 0, 0);
}

void	do_kek(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->f_map->res.y)
	{
		all->f_w.addr[i * all->f_map->res.x] = 0;
	}
	i = -1;
	while (++i < all->f_map->res.y)
	{
		all->f_w.addr[1 + i * all->f_map->res.x] = 0;
	}
}

static void	new_iter_sprite(int i, int *sprite_step, float *max, float step)
{
	if (i >= *max)
	{
		*max += step;
		(*sprite_step)++;
	}
}

void	sprite_to_image(t_all *all, t_point start, int high, int n)
{
	int		i;
	int		j;
	float	ratio_ij[2];
	int		ij_s[2];

	ratio_ij[0] = (float)high / (float)all->ts.spite.width;
	if (high > all->f_map->res.y)
		return ;
	ij_s[0] = 0;
	i = 0;
	while (i < high)
	{
		if (all->a_d_w[start.x + i] < all->spr_loc[n].dist)
		{
			new_iter_sprite(i++, &ij_s[0], &ratio_ij[0],
				   (float)high / (float)all->ts.spite.width);
			continue ;
		}
		ij_s[1] = 0;
		j = -1;
		ratio_ij[1] = (float)high / (float)all->ts.spite.width;
		while (++j < high && start.y + j < all->f_map->res.y)
		{
			if (start.x + i > all->f_map->res.x || start.x + i < 0)
				continue ;
			if (all->ts.spite.addr[ij_s[0]
								   + all->ts.spite.width * ij_s[1]] != 0x000000)
				all->f_w.addr[start.x + i + (start.y + j) * all->f_map->res.x]
					= all->ts.spite.addr[ij_s[0]
										 + all->ts.spite.width * ij_s[1]];
			new_iter_sprite(j, &ij_s[1], &ratio_ij[1],
				   (float)high / (float)all->ts.spite.width);
		}
		new_iter_sprite(i++, &ij_s[0], &ratio_ij[0],
			(float)high / (float)all->ts.spite.width);
	}
}
