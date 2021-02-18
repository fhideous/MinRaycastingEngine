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

	bn = mas;
	while(mas && *mas)
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
	map->e_texture = NULL;
	free(map->s_texture);
	map->s_texture = NULL;
	free(map->w_texture);
	map->w_texture = NULL;
	free(map->n_texture);
	map->n_texture = NULL;
	free(map->sprite);
	map->sprite = NULL;
	ss_free(map->map);
}

int main()
{
	int fd;
	int i;
	char *path = "../map.cub";
	t_all		game;
	t_cub_map full_map;

	fd = open(path, O_RDONLY);
	parse_set(&full_map, fd);
	game.map = full_map.map;
	find_player(game.map, &game.plr);
//	i = -1;
//	while (full_map.map[++i])
//		ft_putendl_fd(full_map.map[i], 1);



	free_map(&full_map);
	close(fd);
	return 0;
}
