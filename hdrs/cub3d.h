#ifndef CUB3D_H
#define CUB3D_H

/*1111111111111111111
1 1111   1    1 1 1
1     1   1      01
1  111    1   1 1 1
1 1     0 1       1
1  1111 0 1   1 1 1
1       0         1
1 1 1 1 0 1 1 1 1 1
1 00    0     0 0 1
1111    00    11111
1  1    0 0       1
1 11   00000011 111
1 1    101   1    1
1     1111 1 1    1
1111111111111111111*/


/*

1111111111111111111111111111111111
1000000000000000000000000000000001
1000000000000000000000000000000001
1000000000000000000000000000000001
10000000000000000000000000000000E1
10000000000000000000000000000000011111111111111111111111111111111111111
1000000000000000000000000000000001
1000000000000000000000000000000001
1000000000000000000000000000000001
1000000000000000000000000000000001
1111111111111111111111111111111111
*/



#define ABS(a) ((a) < 0 ? -(a) : (a))

#include "../lib//libft.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define SPRITES_MAX 128
#define LEN_STEP 0.05
#define M_PI_6_N -0.523598776
#define M_PI_6 0.523598776

#define M_PI_3 1.047197551
#define M_PI_6 0.523598776
#define M_PI_12 0.261799388
#define M_PI_3 1.047197551
#define M_PI_12 0.261799388

#define M_PI_12 0.261799388
/*
 * len of player vector
 */
#define STEP_X 1
#define STEP_Y 1


#define SPEED_X 16
#define SPEED_Y 16
#define ROTATE_SPEED 0.2
#define SPEED 0.087266463


/*
 * window
 */

typedef struct	s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*addr;
	int				line_length;
	int				bits_per_pixel;
	int				endian;
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
	unsigned char flag;
}				  t_color;


/*
 * map
 */

typedef struct s_error
{
	int				error_numb;
	char			*message;
}		t_error;


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
	t_error		error;
}				  t_cub_map;

typedef struct	s_sprite
{
	void			*img_tmp;
	unsigned int 	*addr;
	float			angle;
	float			k;
	int				width;
	int				heigh;
}				t_sprite;

typedef struct	s_texture
{
	void			*img_tmp;
	unsigned int	*addr;
	int				width;
	int				heigh;
}				t_texture;

typedef struct s_textures
{
	t_texture		n_tex;
	t_texture		s_tex;
	t_texture		w_tex;
	t_texture		e_tex;
	t_texture 		spite;

}				t_textures;

//typedef struct s_sprites_crds
//{
//	int				n;
//	t_point			*coordints;
//}				t_sprites_crds;

typedef struct s_sprite_dist_data
{
	float	x;
	float	y;
	float	angle;
	float	dist;
}				t_sprite_dist_data;


typedef struct s_sprites_distns
{
	float 	dist;
	float 	angle;
	int		width;
	t_point	coord;

}				t_sprites_distns;

typedef struct s_sprites
{
	int					size;
	t_point				*points;
//	t_point				*coords;
	t_sprites_distns	*distns;
	float 				*angle_sprite_start;
}				t_sprites;



typedef struct	s_all
{
	t_win				full_win;
	t_plr				plr;
	t_textures			textrs;
	t_cub_map			*full_map;

//	t_sprites_crds		sprts_crds;
	t_sprites			sprites_loc;
	float 				*all_distns_1;

}				  t_all;

char		**get_map(int fd, char *line);
int			find_sprites(char **map, t_sprites *sprts);
int			add_point(t_point *, int , int);
void		message(int err);

int			parse_set(t_cub_map *, int);
int			find_player(char **, t_plr *, int);

void		sprites_zero(t_point *);
void		sprites_dist_sero (t_sprites_distns *);

void		ft_rotate(t_ray *x, t_ray *y, float angle);
int			add_ray(t_all *all,const t_point *, float );
void		add_scale_line(const t_all *all, int n, int hign, const t_texture *textr, int is_x);

int			create_win(t_all *);

void		my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color);
t_texture	texture_define(const t_ray *ray_new, const t_textures *all_txtr, int *is_x);

void		scene_put(t_all *vars, t_cub_map *);
void		print_ray(t_win *, t_ray *start, t_ray *end, float);
void		add_pixel_size(unsigned  int *w_addr,unsigned  int *addr, int x, int y);
int			find_crossing(t_all *all, float  angle, t_win *win, t_texture *txtr);

void		free_map(t_cub_map *map);
int			key_commands(int keycode, t_all *all);
void		screenshot(t_all *all);
void		ft_close(t_all *all);
#endif
