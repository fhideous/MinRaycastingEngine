#ifndef CUB3D_H
#define CUB3D_H

#define ABS(a) ((a) < 0 ? -(a) : (a))
#include "../lib//libft.h"
#include <math.h>
#include <mlx.h>
#include "stdio.h"
#include "stdlib.h"

#define ANGLE_STEP 0.02
#define M_PI_6_N -0.523598776
#define M_PI_6 0.523598776
#define M_PI_12 0.261799388
/*
 * len of player vector
 */
#define STEP_X 1
#define STEP_Y 1


#define SPEED_X 6
#define SPEED_Y 6
#define ROTATE_SPEED 0.05


/*
 * window
 */

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	unsigned int	*addr;
//	char		*addr;
//	void	*addr;
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

typedef struct	s_sprite
{
	void 	*img_tmp;
	unsigned  int	*addr;
	float	angle;
	float	k;
	int		width;
	int		heigh;
}				t_sprite;

typedef struct	s_texture
{
	void 	*img_tmp;
	unsigned  int	*addr;
//	char	*addr;
//
//		void	*addr;
	int		width;
	int		heigh;
}				t_texture;

typedef struct s_textures
{
	t_texture		n_tex;
	t_texture		s_tex;
	t_texture		w_tex;
	t_texture		e_tex;
	t_sprite 		spite;

}				t_textures;

typedef struct s_sprites_crds
{
	int		n;
	t_point	*coordints;
}				t_sprites_crds;

typedef struct s_sprites_distns
{
	float 	dist;
	float 	angle;
}				t_sprites_distns;

typedef struct	s_all
{
	t_win				*full_win;
	t_plr				plr;
	t_textures			textrs;
	t_sprites_crds		sprts_crds;
	t_sprites_distns	*spr_distans;
	t_cub_map			*full_map;
}				  t_all;

char		**get_map(int fd, char *line);
int			find_sprites(char **map, t_sprites_crds *sprts);

int			parse_set(t_cub_map *, int);
int			find_player(char **, t_plr *, int);

void		ft_rotate(t_ray *x, t_ray *y, float angle);
int			add_ray(t_all *all,const t_point *);

int			create_win(t_all *);

void		my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color);

void 		scene_put(t_all *vars, t_cub_map *);
void		print_ray(t_win *, t_ray *start, t_ray *end, float);
void		distance_sprites(const t_sprites_crds *, const t_plr*, t_sprites_distns *);
void		add_pixel_size(unsigned  int *w_addr,unsigned  int *addr, int x, int y);
void		find_crossing(t_all *all, float  angle, t_win *win, t_texture *txtr);

void		free_map(t_cub_map *map);


int			key_commands(int keycode, t_all *all);

#endif
