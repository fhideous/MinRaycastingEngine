#ifndef CUB3D_H
#define CUB3D_H

#include "../lib//libft.h"
#include <math.h>
#include <mlx.h>
#include "stdio.h"
#include "stdlib.h"

#define SCALE 32
#define ANGLE_STEP 1
/*
 * len of player vector
 */
#define STEP_X 5
#define STEP_Y 5

/*
 * window
 */

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_length;
	int			bits_per_pixel;
	int			endian;
}				  t_win;

/*
 * point
 */

typedef struct	s_point
{
	int			x;
	int			y;
}				  t_point;

/*
 * player
 */


typedef struct	s_ray
{
	float		x;
	float		y;
	float		len;
	float		angle;
}				  t_ray;

typedef struct	s_plr
{
	float		x;
	float		y;
	t_ray		ray;
}				  t_plr;


typedef struct	s_color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}				  t_color;


/*
 * map
 */

typedef struct	s_cub_map
{
	t_point 	resolution;
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char 		*sprite;
	t_color		fl_color;
	t_color		cel_color;

	char		**map;
}				  t_cub_map;

typedef struct	s_all
{
	t_win		*full_win;
	t_plr		plr;
	char		**map;
	t_cub_map	*full_map;
}				  t_all;

char		**get_map(int fd, char *line);
int			parse_set(t_cub_map *, int);
int			find_player(char **, t_plr *);

void		ft_rotate(t_ray *x, t_ray *y, float angle);
int			add_ray(t_all *all,const t_point *);

int			create_win(t_cub_map *, t_all *);

void		my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color);

void 		scene_put(t_all *vars, t_cub_map *);
void		print_ray(t_win *, t_ray *start, t_ray *end, float);
void		free_map(t_cub_map *map);


int			key_commands(int keycode, t_all *all);

#endif
