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
	int i;

	i = ft_strlen(*mas);
	bn = mas;
	while(i--)
	{
//		printf("%s\n", *mas);
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
	free(map->sprite);
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
	if (!tex->addr)
		return -1;
	return 0;
//	free(tex);
//	mlx_destroy_image(win->mlx, tex->img_tmp);
}

/*
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
*/

int	texture_open(t_all all, t_textures *textrs)
{
	int err;
	int i;

	err = 0;
	err += get_xpm_addr(&all.full_win, &textrs->n_tex, &all.full_map->n_texture);
	err += get_xpm_addr(&all.full_win, &textrs->s_tex, &all.full_map->s_texture);
	err += get_xpm_addr(&all.full_win, &textrs->e_tex, &all.full_map->e_texture);
	err += get_xpm_addr(&all.full_win, &textrs->w_tex, &all.full_map->w_texture);
	if (textrs->s_tex.width != textrs->n_tex.width ||
			textrs->s_tex.width != textrs->e_tex.width ||
			textrs->s_tex.width != textrs->w_tex.width) {
		//textures must have a one size;
		return (13);
	}
	err += get_xpm_addr(&all.full_win, &textrs->spite, &all.full_map->sprite);
	if (err != 0)
		//wrong path to textures/sprite;
		return (12);
	return (0);
}

/*
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
*/

/*
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
*/

void float_dists_zero(float *distns, int res)
{
	int i;

	i = 0;

	while (i < res)
	{
		distns[i] = 0;
		i++;
	}
}

void message2(int err)
{
	if (err == 10)
		printf("To much paths fields");
	else if (err == 11)
		printf("Path field has wrong number of arguments");
	else if (err == 21)
		printf("Wrong bit map");
	else if (err == 13)
		printf("Fuck you and your color");
	else if (err == 14)
		printf("");
	else if (err == 15)
		printf("");
	else if (err == 16)
		printf("");
	else if (err == 17)
		printf("");
	else if (err == 18)
		printf("");

}

void message(int err)
{
	if (err == 0)
		return;
	if (err > 9)
		message2(err);
	else if (err == 1)
		//ft_printf
		printf("");
	else if (err == 2)
		printf("To much R fields");
	else if (err == 3)
		printf("R field has wrong number of arguments");
	else if (err == 4)
		printf("R field has non digit sumbols");
	else if (err == 5)
		printf("Wow, memory error");
	else if (err == 6)
		printf("To much color fields");
	else if (err == 7)
		printf("Color field has wrong number of arguments");
	else if (err == 8)
		printf("Color field has non digit symbols");
	else if (err == 9)
		printf("Color must include only [0:255] numbers");
	exit(err);
}

int	check_opposite_sign(char **map, int i, int j, int sign)
{
	if (map[i][j + sign] == '\0')
		return -1;
	if (map[i + sign][j] == '\0')
		return -1;
	if (map[i + sign][j + sign] == '\0')
		return -1;
	if (map[i - sign][j + sign] == '\0')
		return -1;
	return 0;
}


int check_opposite(char **map, int i, int j)
{
	int flag;
	flag = check_opposite_sign(map, j, i, 1);
	flag += check_opposite_sign(map, j, i, -1);
	if (flag != 0)
		return -1;
	return 0;
}

int		map_validate(char **map)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (map[j] && map[j][0])
	{
		if (map[j][0] != '1' && map[j][0] != ' ')
			return 20;
		j++;
	}
	while (map[0] && map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			return 20;
		i++;
	}
	i = 1;
	j = 1;

	while (map[j] && map[j][i])
	{
		while(map[j][i])
			i++;
		if (map[j ][i - 1] != '1' && map[j][i - 1] != ' ')
			return 20;
		j++;
		i = 0;
	}
	i = 1;
	j = 1;
	while (map[j] && map[j][i])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0')
				if (check_opposite(map, i, j) == -1)
					return 20;
			i++;
		}
		j++;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int		fd;
	char	*path= "../map.cub";
	int		error;

//	float_dists_zero(all_distns_wall, 1920);
	//	char *texture = "textures/brick.xpm";
	t_cub_map full_map;
	t_all 		all;

	all.size_sprites = -1;
	fd = open(path, O_RDONLY);
	error = parse_set(&full_map, fd);
	all.full_map = &full_map;
	error += map_validate(all.full_map->map);
	if (error) {
		message(error);
	}
	all.full_win.mlx = mlx_init();
	error = texture_open(all, &all.textrs);;
	message(error);

	find_sprites(all.full_map->map, &all);
	if(find_player(all.full_map->map, &all.plr, all.textrs.n_tex.width)) {
		all.full_map->error.error_numb = 13;
		message(error);
	}
	create_win(&all);
	return 0;
}
