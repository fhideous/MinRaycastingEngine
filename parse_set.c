#include "hdrs/cub3d.h"

int	check_errors(char **res, t_point *resolution)
{
	if (!res)
		return (5);
	if (dp_len(res) != 2)
		return (3);
	if (!digits_in_str(res[0]) || !digits_in_str(res[1]))
		return (4);
	if (ft_strlen(res[0]) > 4)
	{
		resolution->x = 1920;
		resolution->y = ft_atoi(res[1]);
	}
	if (ft_strlen(res[1]) > 4)
	{
		if (resolution->x != 1920)
			resolution->x = ft_atoi(res[0]);
		resolution->y = 1080;
	}
	if (ft_strlen(res[0]) > 4 || ft_strlen(res[1]) > 4)
	{
		ft_free_R(res);
		return (0);
	}
	return (1);
}

int	parse_path(const char *line, char **path)
{
	char	**res;

	(line) += 2;
	if (*path != NULL)
		return (10);
	res = ft_split(line, ' ');
	if (!res)
		return (5);
	if (dp_len(res) != 1)
		return (11);
	*path = res[0];
	return (0);
}

int	parse_res(char **line, t_cub_map *f_map)
{
	int		res_x;
	char	**res;
	int		error;

	if (f_map->res.x || f_map->res.y)
		return (2);
	(*line)++;
	res = ft_split(*line, ' ');
	error = check_errors(res, &f_map->res);
	if (error != 1)
		return (error);
	res_x = ft_atoi(res[0]);
	if (res_x > 1920)
		res_x = 1920;
	f_map->res.x = res_x;
	res_x = ft_atoi(res[1]);
	if (res_x > 1080)
		res_x = 1080;
	if (f_map->res.y < 480)
		f_map->res.y = 480;
	if (f_map->res.x < 640)
		f_map->res.x = 640;
	f_map->res.y = res_x;
	ft_free_R(res);
	return (0);
}

int	choise_type(int fd, char *line, t_cub_map *f_map)
{
	int	err;

	err = 0;
	if (*line == 'R')
		err = parse_res(&line, f_map);
	else if (*line == 'F')
		err = parse_color(&f_map->fl_c, &line);
	else if (*line == 'C')
		err = parse_color(&f_map->cl_c, &line);
	else if (!ft_strncmp(line, "SO", 2))
		err =parse_path(line, &f_map->n_t);
	else if (!ft_strncmp(line, "NO", 2))
		err =parse_path(line, &f_map->s_t);
	else if (!ft_strncmp(line, "WE", 2))
		err = parse_path(line, &f_map->w_t);
	else if (!ft_strncmp(line, "EA", 2))
		err = parse_path(line, &f_map->e_t);
	else if (*line == 'S')
		err = parse_path(line, &f_map->s);
	else if (*line == ' ' || *line == '1')
		f_map->map = get_map(fd, line, &err);
//	if (f_map->map == NULL)
//		free(line);
	return (err);
}

int	parse_set(t_cub_map *full_map, int fd)
{
	char	*line;
	int		error;

	full_map_init(full_map);
	while (get_next_line(fd, &line) == 1)
	{
		error = choise_type(fd, line, full_map);
		if (error > 0)
			message(error);
	}
	if (!check_all_fields(full_map))
		return (17);
	free(line);
	close(fd);
	return (0);
}
