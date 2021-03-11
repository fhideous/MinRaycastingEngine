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
//	map->e_texture = NULL;
	free(map->s_texture);
//	map->s_texture = NULL;
	free(map->w_texture);
//	map->w_texture = NULL;
	free(map->n_texture);
//	map->n_texture = NULL;
	free(map->sprite);
//	map->sprite = NULL;
	ss_free(map->map);
}


//typedef struct  s_data {
//	void        *img;
//	char        *addr;
//	int         bits_per_pixel;
//	int         line_length;
//	int         endian;
//}               t_data;
//
//typedef struct  s_vars1 {
//	void    	    *mlx;
//	void    	    *win;
//	t_data			*data_im;
//	struct n_map	*map;
//}               t_vars1;

#include <math.h>

int main()
{
	int fd;
	int i;
	char *path = "../map.cub";
//	char *texture = "textures/brick.xpm";
	t_cub_map full_map;
	t_all 		all;


	fd = open(path, O_RDONLY);
	parse_set(&full_map, fd);


	all.map = full_map.map;
	find_player(all.map, &all.plr);


	create_win(&full_map, &all);

	mlx_destroy_window(all.full_win->mlx, all.full_win->win);
	return 0;
}
