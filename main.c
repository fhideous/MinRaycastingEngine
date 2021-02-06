#include <stdio.h>
#include "minilibx_opengl_20191021/mlx.h"
#include "hdrs/map_puuser.h"
#include <fcntl.h>

#define RES_X	1920
#define RES_Y	1080




typedef struct  s_pos
{
	int			x;
	int			y;
	int		color;

}				t_pos;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct  s_vars {
	void    	    *mlx;
	void    	    *win;
	t_data			*data_im;
	t_pos			pos;
	struct n_map	*map;
}               t_vars;

void pos_init(t_pos *pos)
{
	pos->x = RES_X / 2;
	pos->y = RES_Y / 2;
	pos->color = 0xFF0000;
}

int             key_commands(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == 3)
		vars->pos.color = 0xFF0000;
	if (keycode == 4)
		vars->pos.color = 0x00FF00;
	if (keycode == 2)
		vars->pos.x+= 10;
	if (keycode == 0)
		vars->pos.x-= 10;
	if (keycode == 13)
		vars->pos.y-= 10;
	if (keycode == 1)
		vars->pos.y+= 10;
}

void            my_mlx_pixel_put(t_data *data, int x, int y,unsigned int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


#define STEP 280

void put_n_pixel(t_vars *vars, int i, int j, int n, unsigned int color)
{
	int it;
	int jt;

	it = -1;
	jt = -1;
	while (++it < n )
	{
		while (++jt < n)
			my_mlx_pixel_put(vars->data_im, jt + i + STEP,
							 it + j + STEP, color);
		jt = -1;
	}
}

void	grad_line_top(t_data *img, int color, int width)
{
	int 	i;
	int		j;
	static	int rofl;
	int len;
	int lol;

	len	= 255 * 7;
	lol	= len / 255;
	i	= -1;
	j	= -1;
	while (++i < len)
	{
		while (++j < width)
			my_mlx_pixel_put(img, i , j + rofl, color);
		j = -1;
		if(i % lol == 0)
			color++;
	}
	rofl += width;
}

void 		scene_put(t_vars *vars, unsigned int color)
{
	struct n_map *start;
	int i;
	int j;
	int n;

	n = 25;
	i = 0;
	j = 0;
	start = vars->map;
	while (vars->map)
	{
		while (*(vars->map->line))
		{
			if(*(vars->map->line) == '1')
				put_n_pixel(vars,i, j, n, color);
			if (*(vars->map->line) == '2')
				put_n_pixel(vars,i, j, n, 0xE3CC87);
			if(*(vars->map->line) == '0')
				put_n_pixel(vars,i, j, n, 0xF0958659);
			if (*(vars->map->line) == 'N')
				put_n_pixel(vars,i, j, n, 0xE3D29F);
			i +=n;
			vars->map->line++;
		}
		vars->map->line -= i/n;
		i = 0;
		j += n;
		vars->map = vars->map->n;
	}
	vars->map = start;
//	mlx_put_image_to_window(vars->mlx, vars->win, vars->data_im->img, 0, 0);
}

int     render_next_frame(t_vars *vars)
{
	t_data		img;
	static int color = 0xFC69900;
	static int cnt = 0;
	static int i = 1;
//	mlx_hook(vars->win, 2, 1L << 0, key_commands, &vars);

	img.img = mlx_new_image(vars->mlx, RES_X, RES_Y);

	vars->data_im = &img;
	vars->data_im->addr = mlx_get_data_addr(vars->data_im->img,
			 					&vars->data_im->bits_per_pixel,
				 					&vars->data_im->line_length,
										 &vars->data_im->endian);

		scene_put(vars, 0xC6AC5B);
		for(int j = 0; j < 15; j++)
			for (int i = 0; i < 15; i++)
				my_mlx_pixel_put(vars->data_im, vars->pos.x + i, vars->pos.y
				+ j,color);
//		my_mlx_pixel_put(vars->data_im, vars->pos.x, vars->pos.y,
//					 vars->pos.color);
//	grad_line_top(vars->data_im, 0xFC69900, 20);
	color += i;
	cnt += i;
	if (cnt == 255)
		i = -1;
	if(cnt == 0)
		i = 1;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->data_im->img, 0, 0);
}

int main()
{
	void    *mlx;
	void	*mlx_win;
	t_vars      vars;
	t_data		img;
	int fd;
//	struct n_map *map;

	fd = open("../map.noncub", O_RDONLY);
	if (fd <= 0)
		return (1);
	vars.map = get_map(fd);
	vars.mlx = mlx_init();
	pos_init(&vars.pos);
	vars.win = mlx_new_window(vars.mlx, RES_X, RES_Y, "Hello world!");
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_commands, &vars);
	mlx_loop(vars.mlx);


	return 0;
}
