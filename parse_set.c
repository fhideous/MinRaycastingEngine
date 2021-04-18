#include "hdrs/cub3d.h"
#include "lib/libft.h"
#include "hdrs/get_next_line.h"


void skip_spaces(char **line)
{
	while(**line == ' ')
		(*line)++;
}

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
		//to many paths fields
		return 10;
	res = ft_split(line, ' ');
	if (!res)
		//memory oooops
		return 5;
	if (dp_len(res) != 1)
		//path field has wrong number of arguments
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

int		parse_res(char **line, t_cub_map *f_map)
{
	int res_x;
	char **res;

	if (f_map->resolution.x || f_map->resolution.y)
		//to many R fields
		return 2;
	(*line)++;
	res = ft_split(*line, ' ');
	if (!res)
		//memory oooops;
		return 5;
	if (dp_len(res) != 2)
		//R field has wrong number of arguments
		return 3;
	if (!digits_in_str(res[0]) || !digits_in_str(res[1]))
		//R field has non digit symbols
		return 4;
	res_x = ft_atoi(res[0]);
	f_map->resolution.x = res_x;
	f_map->resolution.y = ft_atoi(res[1]);
	free(res[1]);
	free(res[0]);
	free(res);
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
		//memory ooops;
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
	if (color < 255)
		return color;
	(*flag) += 1;
}

int parse_color(t_color *color, char **line)
{
	char **res;
	unsigned  char flag;

	if (color->flag)
		//to many color fields
		return 6;
	(*line)++;
	res = ft_split(*line, ',');
	if (!res)
		//memory ooooops
		return 5;
	if (dp_len(res) != 3)
		//color field has wrong number of arguments
		return 7;
	if(!digits_in_str(res[0]) || !digits_in_str(res[1]) || !digits_in_str(res[2]))
		//color field has non digit symbols
		return 8;
	flag = check_valid_colors(res);
	color->R = check_valid_color(ft_atoi(res[0]), &flag);
	color->G = check_valid_color(ft_atoi(res[1]), &flag);
	color->B = check_valid_color(ft_atoi(res[2]), &flag);
	if (flag != 0)
		//color must include only [0: 255] numbers
		return 9;
	color->flag = 1;
	free(res[2]);
	free(res[1]);
	free(res[0]);
	free(res);
	return (0);
}

int choise_type(int fd, char *line, t_cub_map *f_map)
{
	int err;

	err = 0;
	if(*line == 'R')
		err = parse_res(&line, f_map);
	else if(*line == 'F')
		err = parse_color(&f_map->fl_color, &line);
	else if(*line == 'C')
		err = parse_color(&f_map->cel_color, &line);
	else if(!ft_strncmp(line, "NO", 2))
		err =parse_path(line, &f_map->n_texture);
	else if(!ft_strncmp(line, "SO", 2))
		err =parse_path(line, &f_map->s_texture);
	else if(!ft_strncmp(line, "WE", 2))
		err = parse_path(line, &f_map->w_texture);
	else if(!ft_strncmp(line, "EA", 2))
		err = parse_path(line, &f_map->e_texture);
	else if(*line == 'S')
		err = parse_path(line,&f_map->sprite);
	else if(*line == ' ' || *line == '1')
	{
		f_map->map = get_map(fd, line);
		return (-42);
	}
	return (err);
}

void full_map_init(t_cub_map *full_map)
{
	full_map->resolution.x = 0;
	full_map->resolution.y = 0;
	full_map->fl_color.flag = 0;
	full_map->cel_color.flag = 0;
	full_map->map = NULL;
	full_map->n_texture = NULL;
	full_map->e_texture = NULL;
	full_map->s_texture = NULL;
	full_map->w_texture = NULL;
	full_map->sprite = NULL;
	full_map->error.error_numb = 0;
	full_map->error.message = NULL;
}

/*
 * 5 mean map
 */

int parse_set(t_cub_map *full_map, int fd)
{
	char *line;
	char *line_bn;
	int error;

	full_map_init(full_map);
	while (get_next_line(fd, &line) == 1)
	{
		line_bn = line;
		error = choise_type(fd, line, full_map);
//		if(error == -42)
//			free(line_bn); else
		if (error > 0)
		{
			full_map->error.error_numb = error;
			return (error);
		}
	}
	free(line);
	close(fd);
	return 0;
}