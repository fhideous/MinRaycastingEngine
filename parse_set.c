#include "hdrs/cub3d.h"
#include "lib/libft.h"
#include "hdrs/get_next_line.h"

int		dp_len(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return i;
}

int		parse_path(const char *line, char **path)
{
	(line) += 2;
	char **res;

	if (*path != NULL)
		return 10;
	res = ft_split(line, ' ');
	if (!res)
		return 5;
	if (dp_len(res) != 1)
		return 11;
	*path = res[0];
	return (0);
}

int		digits_in_str(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return 0;
		i++;
	}
	return 1;
}

void	ft_free_R(char **res)
{
	free(res[1]);
	free(res[0]);
	free(res);
}

int		check_error(char **res, t_point *resolution)
{
	if (!res)
		return 5;
	if (dp_len(res) != 2)
		return 3;
	if (!digits_in_str(res[0]) || !digits_in_str(res[1]))
		return 4;
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

int		parse_res(char **line, t_cub_map *f_map)
{
	int		res_x;
	char	**res;
	int		error;

	if (f_map->res.x || f_map->res.y)
		return 2;
	(*line)++;
	res = ft_split(*line, ' ');
	error = check_error(res, &f_map->res);
	if (error != 1)
		return error;
	res_x = ft_atoi(res[0]);
	if (res_x > 1920)
		res_x = 1920;
	f_map->res.x = res_x;
	res_x = ft_atoi(res[1]);
	if(res_x > 1080)
		res_x = 1080;
	if (f_map->res.y < 480)
		f_map->res.y = 480;
	if (f_map->res.x < 640)
		f_map->res.x = 640;
	f_map->res.y = res_x;
	ft_free_R(res);
	return (0);
}

int check_valid_colors(char **colors)
{
	char **colors_tmp;
	int i;

	i = 0;
	while (colors[i])
	{
		colors_tmp = ft_split(colors[i], ' ');
		if (!colors_tmp)
			return 5;
		if (dp_len(colors_tmp) != 1)
			return 1;
		i++;
	}
	while (i--)
		free(colors_tmp[i]);
	free(colors_tmp);
	return 0;
}

int check_valid_color(int color, unsigned char *flag)
{
	if (color <= 255)
		return color;
	(*flag) += 1;
}

int is_only_three_digits(char **color)
{
	int i;
	int j;
	int cnt;

	i = 0;
	while (i < 3)
	{
		j = 0;
		cnt = 0;
		while (color[i][j])
		{
			if (ft_isdigit(color[i][j]))
				cnt++;
			j++;
		}
		if (cnt > 3)
			return 0;
		i++;
	}
	return 1;
}

void	check_RGB(t_color *color, char **res, unsigned char *flag)
{
	color->R = check_valid_color(ft_atoi(res[0]), flag);
	color->G = check_valid_color(ft_atoi(res[1]), flag);
	color->B = check_valid_color(ft_atoi(res[2]), flag);
}

void	free_RGB(char **res)
{
	free(res[2]);
	free(res[1]);
	free(res[0]);
	free(res);
}

int parse_color(t_color *color, char **line)
{
	char			**res;
	unsigned char	flag;

	if (color->flag)
		return 6;
	(*line)++;
	res = ft_split(*line, ',');
	if (!res)
		return 5;
	if (dp_len(res) != 3)
		return 7;

	if(!digits_in_str(res[0]) || !digits_in_str(res[1]) || !digits_in_str(res[2]))
		return 8;
	flag = check_valid_colors(res);
	check_RGB(color, res, &flag);
	if (flag != 0)
		return 9;
	if (!is_only_three_digits(res))
		return 13;
	color->flag = 1;
	free_RGB(res);
	return (0);
}

int choise_type(int fd, char *line, t_cub_map *f_map)
{
	int err;

	err = 0;
	if(*line == 'R')
		err = parse_res(&line, f_map);
	else if(*line == 'F')
		err = parse_color(&f_map->fl_c, &line);
	else if(*line == 'C')
		err = parse_color(&f_map->cl_c, &line);
	else if(!ft_strncmp(line, "SO", 2))
		err =parse_path(line, &f_map->n_t);
	else if(!ft_strncmp(line, "NO", 2))
		err =parse_path(line, &f_map->s_t);
	else if(!ft_strncmp(line, "WE", 2))
		err = parse_path(line, &f_map->w_t);
	else if(!ft_strncmp(line, "EA", 2))
		err = parse_path(line, &f_map->e_t);
	else if(*line == 'S')
		err = parse_path(line,&f_map->s);
	else if(*line == ' ' || *line == '1')
	{
		f_map->map = get_map(fd, line, &err);
	}
	return (err);
}

void full_map_init(t_cub_map *full_map)
{
	full_map->res.x = 0;
	full_map->res.y = 0;
	full_map->fl_c.flag = 0;
	full_map->cl_c.flag = 0;
	full_map->map = NULL;
	full_map->n_t = NULL;
	full_map->e_t = NULL;
	full_map->s_t = NULL;
	full_map->w_t = NULL;
	full_map->s = NULL;
}


int		check_all_fields(t_cub_map *full_map)
{
	if (full_map->res.x == 0 || full_map->res.y == 0 ||
		full_map->cl_c.flag == 0 || full_map->s == NULL || full_map->fl_c.flag == 0 ||
		full_map->w_t == NULL || full_map->s_t == NULL || full_map->e_t == NULL ||
		full_map->n_t == NULL || full_map->map == NULL)
		return 0;
	return 1;
}

int parse_set(t_cub_map *full_map, int fd)
{
	char *line;
	int error;

	full_map_init(full_map);
	while (get_next_line(fd, &line) == 1)
	{
		error = choise_type(fd, line, full_map);
		if (error > 0)
			message(error);
	}
	if(!check_all_fields(full_map))
		return 17;
	free(line);
	close(fd);
	return 0;
}