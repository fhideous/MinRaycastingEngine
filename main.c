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
	t_win      vars;
	int fd;
	char		**map;
	int i;
	char *path = "../map.cub";
	t_all 		all;
	t_cub_map full_map;

	//	printf("HI");

	fd = open(path, O_RDONLY);

	parse_set(&full_map, fd);
//	map	= get_map(fd);


	all.map = full_map.map;
	all.plr.x = 11 * SCALE;
	all.plr.y = 27 * SCALE;

	all.plr.ray.x = all.plr.x + 0.6 * SCALE;
	all.plr.ray.y = all.plr.y;
	all.plr.ray.len = 0.6 * SCALE;


	all.plr.ray.angle = acos((all.plr.x /
							  sqrt(all.plr.x * all.plr.x +
								   all.plr.y * all.plr.y))) / 57.3;

	create_win(full_map, all, vars);
	i = -1;
	while (full_map.map[++i])
		ft_putendl_fd(full_map.map[i], 1);

	free_map(&full_map);
	close(fd);
	return 0;
}
