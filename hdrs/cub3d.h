#ifndef CUB3D_H
# define CUB3D_H

#include "../lib/libft.h"
# include "get_next_line.h"

# include <math.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define SPRITES_MAX 128
# define LEN_STEP 0.05
# define M_PI_6_N -0.523598776
# define M_PI_6 0.523598776
# define M_PI_3 1.047197551
# define M_PI_6 0.523598776
# define M_PI_12 0.261799388
# define M_PI_3 1.047197551
# define M_PI_12 0.261799388
# define M_PI_12 0.261799388
# define STEP_X 1
# define STEP_Y 1
# define SPEED_X 16
# define SPEED_Y 16
# define ROTATE_SPEED 0.06

typedef struct s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*addr;
	int				l_len;
	int				BPP;
	int				endian;
}		t_win;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_ray
{
	float	x;
	float	y;
	float	len;
	float	angle;
}	t_ray;

typedef struct s_plr
{
	float	x;
	float	y;
	t_ray	ray;
}	t_plr;

typedef struct s_color
{
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
	unsigned char	flag;
}	t_color;

typedef struct s_kek
{
	float	*ratio_ij;
	int		*ij_s;
	float	high;
	t_point	start;
	int		i;
}	t_kek;

typedef struct s_cub_map
{
	t_point	res;
	char	*n_t;
	char	*s_t;
	char	*w_t;
	char	*e_t;
	char	*s;
	t_color	fl_c;
	t_color	cl_c;
	char	**map;
}	t_cub_map;

typedef struct s_texture
{
	void			*img_tmp;
	unsigned int	*addr;
	int				width;
	int				heigh;
}				t_texture;

typedef struct s_textures
{
	t_texture	n_tex;
	t_texture	s_tex;
	t_texture	w_tex;
	t_texture	e_tex;
	t_texture	spite;
	t_texture	c_t;

}				t_textures;

typedef struct s_sprite
{
	t_point	coords;
	float	dist;
	float	angle;
}			t_sprite;

typedef struct s_all
{
	t_win		f_w;
	t_plr		plr;
	t_textures	ts;
	t_cub_map	*f_map;
	int			s_spr;
	int			screen;
	t_sprite	*spr_loc;
	float		a_d_w[1920];
}				t_all;

char		**get_map(int fd, char *line, int *error);
int			find_sprites(char **kek, t_all *all);
void		message(int err);
int			parse_set(t_cub_map *kek, int lol);
int			find_player(char **kek, t_plr *lel, int lol);
void			add_ray(t_all *all, const t_point *kek, float lol);

void		add_scale_line(t_all *all, int n, int hign, int is_x);

void			create_win(t_all *all);
t_texture	texture_define(const t_ray *ray_new,
				const t_textures *all_txtr, int *is_x);
void			find_crossing(t_all *all, float angle, int kek, t_texture *textr);
void		free_map(t_cub_map *map);
void			key_commands(int keycode, t_all *all);
int			find_max(char **map_old, int len);
void		screenshot(t_all *all);
int			ft_close(t_all *all);
int			map_validate(char **map);
void		ft_free_R(char **res);
void		free_RGB(char **res);
void		check_crossing(t_plr *plr, t_all *all, int is_x);
void		go_right(t_plr *plr, t_all *all);
void		go_left(t_plr *plr, t_all *all);
void		go_back(t_plr *plr, t_all *all);
void		go_forward(t_plr *plr, t_all *all);
void		change_angle(t_all *all, float value);
int			parse_color(t_color *color, char **line);
int			digits_in_str(const char *str);
int			dp_len(char **strs);
void		full_map_init(t_cub_map *full_map);
int			check_all_fields(t_cub_map *full_map);
void		add_flour(t_all *all);
void		do_kek(t_all *all);
void		sprite_to_image(t_all *all, t_point start, int high, int n);
void		distance_to_sprites(t_all *all);
void		print_sprite(t_all *all);
void		find_angle_sprite(t_all *all);
void		sprite_sort(t_sprite *sprs_CDA, int size);
t_kek		kek_full(t_point start, float *ratio_ij, int *ij_s, int high);
float		ABS(float a);

#endif
