#include "lib/libft.h"
#include "hdrs/cub3d.h"

static char	**list_to_massive(t_list **hd, size_t len)
{
	char		**map;
	int			i;
	t_list		*tmp;
	t_list		*old;

	map = ft_calloc(len + 1, sizeof(char *));
	if (!map)
		return (NULL);
	tmp = *hd;
	i = -1;
	while (len--)
	{
		old = tmp;
		map[++i] = tmp->data;
		tmp = tmp->next;
		free(old);
	}
	return (map);
}

char	**cal_plus_space(char **map_new, int len_max)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= len_max)
		map_new[i] = ft_calloc(len_max + 1, sizeof(char));
	i = 0;
	while (i < len_max)
	{
		j = 0;
		while (j < len_max)
		{
			map_new[i][j] = ' ';
			j++;
		}
		i++;
	}
}

char	**map_to_square(char **map_old, int len)
{
	char	**map_new;
	int		len_max;
	int		i;
	int		j;

	len_max = find_max(map_old, len);
	map_new = ft_calloc(len_max + 1, sizeof(char *));
	cal_plus_space(map_new, len_max);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (map_old[i][j])
		{
			map_new[i][j] = map_old[i][j];
			j++;
		}
		i++;
	}
	while (i--)
		free (map_old[i]);
	free (map_old);
	return (map_new);
}

int	check_new_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i], "", 4) == 0)
			return (15);
		i++;
	}
	return (0);
}

char	**get_map(int fd, char *line, int *error)
{
	t_list	*hd;
	char	**map;
	char	**square_map;
	int		n_lists;

	*error = 0;
	hd = NULL;
	if (line)
	{
		ft_lstadd_back(&hd, ft_lstnew(line));
		free(line);
	}
	while (get_next_line(fd, &line) == 1)
	{
		ft_lstadd_back(&hd, ft_lstnew(line));
		free(line);
	}
	ft_lstadd_back(&hd, ft_lstnew(line));
	free(line);
	n_lists = ft_lstsize(hd);
	map = list_to_massive(&hd, n_lists);
	*error = check_new_line(map);
	square_map = map_to_square(map, n_lists);
	return (square_map);
}
