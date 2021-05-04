#include "hdrs/cub3d.h"

void	ft_free_R(char **res)
{
	free(res[1]);
	free(res[0]);
	free(res);
}

void	free_RGB(char **res)
{
	free(res[2]);
	free(res[1]);
	free(res[0]);
	free(res);
}

void	ss_free(char **mas)
{
	char		**bn;
	int			i;

	i = ft_strlen(*mas);
	bn = mas;
	while (i--)
	{
		free(*mas);
		*mas = NULL;
		mas++;
	}
	free(bn);
}

void	free_map(t_cub_map *map)
{
	free(map->e_t);
	free(map->s_t);
	free(map->w_t);
	free(map->n_t);
	free(map->s);
	ss_free(map->map);
}
