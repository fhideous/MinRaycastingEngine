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
		free(*mas);
		*mas = NULL;
		mas++;
	}
	free(bn);
}

void	free_map(t_cub_map *map)
{
	free(map->e_texture);
	free(map->s_texture);
	free(map->w_texture);
	free(map->n_texture);
	free(map->sprite);
	ss_free(map->map);
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
	if (!tex->addr)
		return -1;
	return 0;
}

int	texture_open(t_all all, t_textures *textrs)
{
	int err;

	err = 0;
	err += get_xpm_addr(&all.full_win, &textrs->n_tex, &all.full_map->n_texture);
	err += get_xpm_addr(&all.full_win, &textrs->s_tex, &all.full_map->s_texture);
	err += get_xpm_addr(&all.full_win, &textrs->e_tex, &all.full_map->e_texture);
	err += get_xpm_addr(&all.full_win, &textrs->w_tex, &all.full_map->w_texture);
	if (textrs->s_tex.width != textrs->n_tex.width ||
			textrs->s_tex.width != textrs->e_tex.width ||
			textrs->s_tex.width != textrs->w_tex.width) {
		return (13);
	}
	err += get_xpm_addr(&all.full_win, &textrs->spite, &all.full_map->sprite);
	if (err != 0)
		return (12);
	return (0);
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
	else if (err == 19)
		printf("To many players");
	else if (err == 15)
		printf("");
	else if (err == 16)
		printf("");
	else if (err == 17)
		printf("Need more data");
	else if (err == 18)
		printf("Open map");

}

void message(int err)
{
	if (err == 0)
		return;
	printf("Error\n");
	if (err > 9)
		message2(err);
	else if (err == 1)
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
	if (map[i][j + sign] == '\0' || map[i][j + sign] == ' ')
		return -1;
	if (map[i + sign][j] == '\0' || map[i + sign][j] == ' ')
		return -1;
	if (map[i + sign][j + sign] == '\0' || map[i + sign][j + sign] == ' ')
		return -1;
	if (map[i - sign][j + sign] == '\0' || map[i - sign][j + sign] == ' ')
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

//int		check

int		map_validate(char **map)
{
	int		i;
	int		j;
	size_t		ij_max;

	if (!map)
		return 18;
	ij_max = ft_strlen(map[0]);
	j = 0;
	i = 0;
	while (j < ij_max)
	{
		if (map[j][0] != '1' && map[j][0] != ' ')
			return 18;
		j++;
	}
	while (i < ij_max)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			return 18;
		i++;
	}
	i = 1;
	j = 1;
	while (j < ij_max)
	{
		while(i < ij_max)
			i++;
		if (map[j][i - 1] != '1' && map[j][i - 1] != ' ')
			return 18;
		j++;
		i = 0;
	}
	j = 1;
	while (j < ij_max)
	{
		i = 1;
		while (i < ij_max)
		{
			if (map[j][i] == '0')
				if (check_opposite(map, i, j) == -1)
					return 18;
			i++;
		}
		j++;
	}
	return 0;
}

int check_argv(int argc,char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		return -1;
	while (argv[1][i])
		i++;
	if (i <= 4)
		return -1;
	if (argv[1][i - 1] == 'b' && argv[1][i - 2] == 'u' && argv[1][i - 3] == 'c' && argv[1][i - 4] == '.')
		return 0;
	return -1;
}

int main(int argc, char **argv)
{
	int		fd;
	int		error;

	t_cub_map full_map;
	t_all 		all;
	error = check_argv(argc, argv);
	message(error);
	fd = open(argv[1], O_RDONLY);
	all.size_sprites = -1;
	error += parse_set(&full_map, fd);
	message(error);
	all.full_map = &full_map;
	error += map_validate(all.full_map->map);
	message(error);
	all.full_win.mlx = mlx_init();
	error = texture_open(all, &all.textrs);;
	message(error);
	find_sprites(all.full_map->map, &all);
	error = find_player(all.full_map->map, &all.plr, all.textrs.n_tex.width);
	message(error);
	create_win(&all);
	return 0;
}
