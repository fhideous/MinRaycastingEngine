#include "hdrs/cub3d.h"

static int	check_valid_colors(char **colors)
{
	char	**colors_tmp;
	int		i;

	i = 0;
	while (colors[i])
	{
		colors_tmp = ft_split(colors[i], ' ');
		if (!colors_tmp)
			return (5);
		if (dp_len(colors_tmp) != 1)
			return (1);
		i++;
	}
	while (i > 0)
		free(colors_tmp[--i]);
	free(colors_tmp);
	return (0);
}

static int	check_valid_color(int color, unsigned char *flag)
{
	if (color <= 255)
		return (color);
	(*flag) += 1;
}

static int	is_only_three_digits(char **color)
{
	int	i;
	int	j;
	int	cnt;

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
			return (0);
		i++;
	}
	return (1);
}

static void	check_RGB(t_color *color, char **res, unsigned char *flag)
{
	color->R = check_valid_color(ft_atoi(res[0]), flag);
	color->G = check_valid_color(ft_atoi(res[1]), flag);
	color->B = check_valid_color(ft_atoi(res[2]), flag);
}

int	parse_color(t_color *color, char **line)
{
	char			**res;
	unsigned char	flag;

	if (color->flag)
		return (6);
	(*line)++;
	res = ft_split(*line, ',');
	if (!res)
		return (5);
	if (dp_len(res) != 3)
		return (7);
	if (!digits_in_str(res[0])
		|| !digits_in_str(res[1]) || !digits_in_str(res[2]))
		return (8);
	flag = check_valid_colors(res);
	check_RGB(color, res, &flag);
	if (flag != 0)
		return (9);
	if (!is_only_three_digits(res))
		return (13);
	color->flag = 1;
	free_RGB(res);
	return (0);
}
