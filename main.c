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
void	add_pixel_size(unsigned int *w_addr, unsigned int *addr, int x, int y)
{
	int i;
	int j;
	i = -1;
	j = -1;
	while (++i != SCALE_TEX)
	{
		while (++j != SCALE_TEX)
		{
			w_addr[SCALE_TEX * x + j + 640 * (SCALE_TEX * y +i)] = addr[x + y * 32];
		}
		j = -1;
	}
}

void xpm_test(char *path)
{
	t_win win;
	t_texture 	n;
	{
		win.mlx = mlx_init();
		win.win = mlx_new_window(win.mlx, 640,
								 480, "texture");
		n.img_tmp = mlx_xpm_file_to_image(win.mlx, path, &n.width, &n.heigh);
		n.addr = mlx_get_data_addr(n.img_tmp,
								   &win.bits_per_pixel,
								   &win.line_length,
								   &win.endian);
		win.img = mlx_new_image(win.mlx, 640, 480);
		win.addr = mlx_get_data_addr(win.img,
									 &win.bits_per_pixel,
									 &win.line_length,
									 &win.endian);
	}
	int i = 0;
	int j = 0;
	while (i != n.heigh ) {
		while(j != n.width )
		{
			add_pixel_size(win.addr, n.addr, i, j);
			j++;

		}
			j  = 0;
			i++;
	}
	mlx_put_image_to_window(win.mlx,
							win.win, win.img,100 , 100);
	mlx_loop(win.mlx);
}

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

int	texture_open(t_win *win, t_textures *textrs, t_cub_map *cub_map)
{
	int err;

	err = 0;
	err += get_xpm_addr(win, &textrs->n_tex, &cub_map->n_texture);
	err += get_xpm_addr(win, &textrs->s_tex, &cub_map->s_texture);
	err += get_xpm_addr(win, &textrs->e_tex, &cub_map->e_texture);
	err += get_xpm_addr(win, &textrs->w_tex, &cub_map->w_texture);
	if (textrs->s_tex.width != textrs->n_tex.width ||
			textrs->s_tex.width != textrs->e_tex.width ||
			textrs->s_tex.width != textrs->w_tex.width)
		return (-1);
	err += get_xpm_addr_sprite(win, &textrs->spite, &cub_map->sprite);

	return (0);
}

int main()
{
	int fd;
	char *path = "../map.cub";
//	char *texture = "textures/brick.xpm";
	t_cub_map full_map;
	t_all 		all;


	fd = open(path, O_RDONLY);
	parse_set(&full_map, fd);
//
//	xpm_test(full_map.n_texture);
//	return (9);
	all.full_map = &full_map;


	all.full_win = malloc(sizeof (t_win));
	all.full_win->mlx = mlx_init();
	if(texture_open(all.full_win,&all.textrs, all.full_map) == -1)
		exit(32);

	find_player(all.full_map->map, &all.plr, all.textrs.n_tex.width);

	create_win(&all);
//	mlx_destroy_window(all.full_win->mlx, all.full_win->win);
	return 0;
}
