#include "hdrs/cub3d.h"
#include "lib/libft.h"
#include <unistd.h>

int	get_xpm_addr(t_win *win, t_texture *tex, char **path)
{
	tex->img_tmp = mlx_xpm_file_to_image(win->mlx, *path,
			&tex->width, &tex->heigh);
	if (!tex->img_tmp || tex->width != tex->heigh)
		return (-1);
	tex->addr = mlx_get_data_addr(tex->img_tmp,
			   &win->BPP,
			   &win->l_len,
			   &win->endian);
	if (!tex->addr)
		return (-1);
	return (0);
}

int	texture_open(t_all all, t_textures *textrs)
{
	int	err;

	err = 0;
	err += get_xpm_addr(&all.f_w, &textrs->n_tex, &all.f_map->n_t);
	err += get_xpm_addr(&all.f_w, &textrs->s_tex, &all.f_map->s_t);
	err += get_xpm_addr(&all.f_w, &textrs->e_tex, &all.f_map->e_t);
	err += get_xpm_addr(&all.f_w, &textrs->w_tex, &all.f_map->w_t);
	if (textrs->s_tex.width != textrs->n_tex.width
		|| textrs->s_tex.width != textrs->e_tex.width
		|| textrs->s_tex.width != textrs->w_tex.width)
		return (13);
	err += get_xpm_addr(&all.f_w, &textrs->spite, &all.f_map->s);
	if (err != 0)
		return (12);
	return (0);
}

int	check_save(int *screen, char *argv)
{
	if (ft_strncmp(argv, "--save", 6) == 0)
	{
		*screen = 1;
		return (0);
	}
	return (22);
}

int	check_argv(int *screen, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 3 || argc < 2)
		return (22);
	while (argv[1][i])
		i++;
	if (i <= 4)
		return (22);
	if (argv[1][i - 1] == 'b' && argv[1][i - 2] == 'u'
	&& argv[1][i - 3] == 'c' && argv[1][i - 4] == '.')
	{
		if (argc == 3)
			return (check_save(screen, argv[2]));
		else
			*screen = 0;
		return (0);
	}
	return (22);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			error;
	t_cub_map	full_map;
	t_all		all;

	error = check_argv(&all.screen, argc, argv);
	message(error);
	fd = open(argv[1], O_RDONLY);
	all.s_spr = -1;
	error += parse_set(&full_map, fd);
	message(error);
	all.f_map = &full_map;
	error += map_validate(all.f_map->map);
	message(error);
	all.f_w.mlx = mlx_init();
	error = texture_open(all, &all.ts);
	message(error);
	find_sprites(all.f_map->map, &all);
	error = find_player(all.f_map->map, &all.plr, all.ts.n_tex.width);
	message(error);
	create_win(&all);
	return (0);
}
