#include "hdrs/cub3d.h"

void	distance_to_sprites(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->s_spr)
	{
		all->spr_loc[i].dist
			= hypotf(all->plr.x
				- (float)all->spr_loc[i].coords.y
				* (float)all->ts.n_tex.width - 32,
				 all->plr.y
				 - (float)all->spr_loc[i].coords.x
				   * (float)all->ts.n_tex.width - 32);
		i++;
	}
}

void	sprite_sort(t_sprite *sprs_CDA, int size)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i)
		{
			if (sprs_CDA[j].dist < sprs_CDA[j + 1].dist)
			{
				tmp.dist = sprs_CDA[j].dist;
				tmp.coords = sprs_CDA[j].coords;
				tmp.angle = sprs_CDA[j].angle;
				sprs_CDA[j] = sprs_CDA[j + 1];
				sprs_CDA[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	find_angle_sprite(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->s_spr)
	{
		all->spr_loc[i].angle
			= atan2f(all->plr.x - (float)(all->ts.n_tex.width >> 1)
				 - (float)all->spr_loc[i].coords.y
				   * (float)all->ts.spite.width,
				 all->plr.y - (float)(all->ts.n_tex.width >> 1)
				 - (float)all->spr_loc[i].coords.x
				   * (float)all->ts.spite.width);
		all->spr_loc[i].angle += (float)M_PI;
		all->spr_loc[i].angle += (float)(3 * M_PI / 2);
		if (all->spr_loc[i].angle > M_PI + M_PI)
			all->spr_loc[i].angle -= (float)(M_PI + M_PI);
		all->spr_loc[i].angle *= -1;
		all->spr_loc[i].angle += (float)(M_PI + M_PI);
		i++;
	}
}

int	check_valid_angle(float d_angle, float *angle, float *plr_angle)
{
	if (ABS(*angle - *plr_angle) < M_PI_6 + d_angle)
		return (1);
	if (*angle + *plr_angle > M_PI + M_PI - M_PI_6)
	{
		if (*angle > M_PI + M_PI - M_PI_6 && *plr_angle < M_PI_6)
		{
			*angle -= 2 * M_PI;
			return (1);
		}
		else if (*plr_angle > M_PI + M_PI - M_PI_6 && *angle < M_PI_6)
		{
			*plr_angle -= 2 * M_PI;
			return (1);
		}
	}
	return (0);
}

void	print_sprite(t_all *all)
{
	int			i;
	float		high;
	float		x_y;
	t_point		start;
	float		plr_angle_cpy;

	x_y = (float)all->f_map->res.x / (float)all->f_map->res.y;
	i = -1;
	plr_angle_cpy = all->plr.ray.angle;
	while (++i < all->s_spr)
	{
		high = (x_y * (float)all->f_map->res.y
				* (float)all->ts.spite.width / all->spr_loc[i].dist);
		if (!check_valid_angle((float)high * (float)M_PI_6
				   / (float)all->f_map->res.x,
				   &all->spr_loc[i].angle, &plr_angle_cpy))
			continue ;
		start.y = (all->f_map->res.y / 2) - (int)(high / 2);
		start.x = (int)((all->spr_loc[i].angle - plr_angle_cpy)
				* (float)(all->f_map->res.x) / (M_PI_3)) - ((int)high >> 1)
			  + (all->f_map->res.x / 2 );
		sprite_to_image(all, start, (int)high, i);
	}
}
