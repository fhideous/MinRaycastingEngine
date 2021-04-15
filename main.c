#include <stdio.h>
#include "hdrs/map_puuser.h"
#include <fcntl.h>
#include <stdlib.h>
#include "hdrs/cub3d.h"
#include "lib/libft.h"
#include <unistd.h>


void ss_free(char** mas)
{
	char **bn;

	bn = mas;
	while(mas && *mas)
	{
		free(*mas);
		*mas = NULL;
		mas++;
	}
	free(bn);
}

void	free_map(t_cub_map *map)
{
	free(map->e_texture);
//	map->e_texture = NULL;
	free(map->s_texture);
//	map->s_texture = NULL;
	free(map->w_texture);
//	map->w_texture = NULL;
	free(map->n_texture);
//	map->n_texture = NULL;
//	free(map->sprite);
//	map->sprite = NULL;
	ss_free(map->map);
}

#define SCALE_TEX 10


int get_xpm_addr(t_win *win, t_texture *tex, char **path)
{
	tex->img_tmp = mlx_xpm_file_to_image(win->mlx, *path, &tex->width, &tex->heigh);
	if(!tex->img_tmp || tex->width != tex->heigh)
		return -1;
	tex->addr = mlx_get_data_addr(tex->img_tmp,
							   &win->bits_per_pixel,
							   &win->line_length,
							   &win->endian);
//	free(tex);
//	mlx_destroy_image(win->mlx, tex->img_tmp);
}

int get_xpm_addr_sprite(t_win *win, t_sprite *tex, char **path)
{
	tex->img_tmp = mlx_xpm_file_to_image(win->mlx, *path, &tex->width, &tex->heigh);
	if(!tex->img_tmp || tex->width != tex->heigh)
		return -1;
	tex->addr = mlx_get_data_addr(tex->img_tmp,
								  &win->bits_per_pixel,
								  &win->line_length,
								  &win->endian);
//	free(tex);
//	mlx_destroy_image(win->mlx, tex->img_tmp);
}

int	texture_open(const t_all all, t_textures *textrs)
{
	int err;
	int i;

	err = 0;
	err += get_xpm_addr(all.full_win, &textrs->n_tex, &all.full_map->n_texture);
	err += get_xpm_addr(all.full_win, &textrs->s_tex, &all.full_map->s_texture);
	err += get_xpm_addr(all.full_win, &textrs->e_tex, &all.full_map->e_texture);
	err += get_xpm_addr(all.full_win, &textrs->w_tex, &all.full_map->w_texture);
	if (textrs->s_tex.width != textrs->n_tex.width ||
			textrs->s_tex.width != textrs->e_tex.width ||
			textrs->s_tex.width != textrs->w_tex.width) {
		return (-1);
	}
	err += get_xpm_addr(all.full_win, &textrs->spite, &all.full_map->sprite);
//	i = -1;
//	while (++i != all.sprts_crds.n)
//	{
//		all.sprts_crds.coordints[i].x *= textrs->s_tex.width;
//		all.sprts_crds.coordints[i].y *= textrs->s_tex.width;
//	}
	return (err);
}

void sprites_zero(t_point *coords)
{
	t_point tmp;
	int i;

	i = 0;
	tmp.x = 0;
	tmp.y = 0;
	while (i < SPRITES_MAX)
	{
		coords[i] = tmp;
		i++;
	}
}

void sprites_dist_sero (t_sprites_distns *distns)
{
	t_sprites_distns tmp;
	int i;

	i = 0;
	tmp.angle = 0;
	tmp.dist = 0;

	while (i < SPRITES_MAX)
	{
		distns[i] = tmp;
		i++;
	}
}


int main()
{
	int fd;
	char *path = "../map.cub";
//	char *texture = "textures/brick.xpm";
	t_cub_map full_map;
	t_all 		all;
	t_point 		sprites_loc[SPRITES_MAX];
	t_sprites_distns sprites_dist[SPRITES_MAX];
	sprites_dist_sero(sprites_dist);

	all.sprites_loc.points = sprites_loc;
	all.sprites_loc.distns = sprites_dist;
	all.sprites_loc.size = 0;
	fd = open(path, O_RDONLY);
	parse_set(&full_map, fd);

	all.full_map = &full_map;
	find_sprites(all.full_map->map, &all.sprts_crds);
//	all.spr_distans = ft_calloc((all.sprts_crds.n + 1), sizeof(t_sprites_distns));
	all.full_win = malloc(sizeof (t_win));
	all.full_win->mlx = mlx_init();
	if(texture_open(all, &all.textrs) == -1) {
		exit(32);
	}
	find_player(all.full_map->map, &all.plr, all.textrs.n_tex.width);

	create_win(&all);
//	mlx_destroy_window(all.full_win->mlx, all.full_win->win);
	return 0;
}
