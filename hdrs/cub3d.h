#ifndef CUB3D_H
#define CUB3D_H

#include "../lib//libft.h"
#include <math.h>
#define SCALE 16

/*
 * len of player vector
 */
#define STEP_X 0.2
#define STEP_Y 0.2

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

typedef struct s_ray
{
	float			x;
	float			y;
	float 			len;
}				t_ray;

typedef struct	s_plr
{
	float			x;
	float			y;
	t_ray 			dir;
}				  t_plr;

typedef struct	s_all
{
	t_win		*win;
	t_plr		plr;
	char		**map;
}				  t_all;

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

char	**get_map(int fd, char *line);
int		parse_set(t_cub_map *, int);
int		find_player(char **, t_plr *);

#endif
