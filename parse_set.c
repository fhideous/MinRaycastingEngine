#include "hdrs/cub3d.h"
#include "lib/libft.h"
#include "hdrs/get_next_line.h"


void skip_spaces(char **line)
{
	while(**line == ' ')
		(*line)++;
}

int		parse_path(char **line, char **path)
{
	(*line) += 2;
	skip_spaces(line);
	if(!(*path = ft_strjoin(*line, "")))
		return (-1);
	return (0);
}

int		parse_res(char **line, t_cub_map *f_map)
{
	int res_x;

	(*line)++;
	res_x = ft_atoi(*line);
	f_map->resolution.x = res_x;
	skip_spaces(line);
	while(ft_isdigit(**line))
		(*line)++;
	f_map->resolution.y = ft_atoi(*line);
	return (0);
}

int parse_color(t_color *color, char **line)
{
	(*line)++;
	skip_spaces(line);
	color->R = ft_atoi(*line);
	while(ft_isdigit(**line))
		(*line)++;
	while(**line == ' ' || **line == ',')
		(*line)++;
	color->G = ft_atoi(*line);
	while(ft_isdigit(**line))
		(*line)++;
	while(**line == ' ' || **line == ',')
		(*line)++;
	color->B = ft_atoi(*line);
	return (0);
}

int choise_type(int fd, char *line, t_cub_map *f_map)
{
	void *fun;

	if(*line == 'R')
		parse_res(&line, f_map);
	else if(*line == 'F')
		parse_color(&f_map->fl_color, &line);
	else if(*line == 'C')
		parse_color(&f_map->cel_color, &line);
	else if(!ft_strncmp(line, "NO", 2))
		parse_path(&line, &f_map->n_texture);
	else if(!ft_strncmp(line, "SO", 2))
		parse_path(&line, &f_map->s_texture);
	else if(!ft_strncmp(line, "WE", 2))
		parse_path(&line, &f_map->w_texture);
	else if(!ft_strncmp(line, "EA", 2))
		parse_path(&line, &f_map->e_texture);
	else if(*line == 'S')
		parse_path(&line,&f_map->sprite);
	else if(*line == ' ' || *line == '1')
	{
		f_map->map = get_map(fd, line);
		return (5);
	}
	return (0);
}

/*
 * 5 mean map
 */

int parse_set(t_cub_map *full_map, int fd)
{
	char *line;
	char *line_bn;

	while (get_next_line(fd, &line) == 1)
	{
		line_bn = line;
		if((choise_type(fd, line, full_map)) != 5)
			free(line_bn);
	}
	free(line);
}