#include <stdio.h>
#include "minilibx_opengl_20191021/mlx.h"

#define RES_X	1920
#define RES_Y	1080




//
//void	grad_line_top(t_data *img, int color, int width)
//{
//	int 	i;
//	int		j;
//	static	int rofl;
//	int len;
//	int lol;
//
//	len	= 255 * 7;
//	lol	= len / 255;
//	i	= -1;
//	j	= -1;
//	while (++i < len)
//	{
//		while (++j < width)
//			my_mlx_pixel_put(img, i , j + rofl, color);
//		j = -1;
//		if(i % lol == 0)
//			color++;
//	}
//	rofl += width;
//}

//int             key_hook(int keycode, t_vars *vars)
//{
//	printf("Hello from key_hook!\n");
//
//	vars->data_im->img = mlx_new_image(vars->mlx, 1920, 1080);
//	vars->data_im->addr = mlx_get_data_addr(vars->data_im->img,
//	 &vars->data_im->bits_per_pixel,&vars->data_im->line_length,
//								&vars->data_im->endian);
//	grad_line_top(vars->data_im, 0xFF5700, 20);
//	mlx_put_image_to_window(vars->mlx, vars->win, vars->data_im->img, 0, 0);
//	mlx_loop(vars->mlx);
//}
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
	void        *mlx;
	void        *win;
	t_data		*data_im;
	t_pos		pos;
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

void			scene_put(t_data *data, unsigned int color)
{

}

int     render_next_frame(t_vars *vars)
{
	t_data		img;

//	mlx_hook(vars->win, 2, 1L << 0, key_commands, &vars);

	img.img = mlx_new_image(vars->mlx, RES_X, RES_Y);

	vars->data_im = &img;
	vars->data_im->addr = mlx_get_data_addr(vars->data_im->img,
			 					&vars->data_im->bits_per_pixel,
				 					&vars->data_im->line_length,
										 &vars->data_im->endian);

//		scene_put(vars->data_im, 0xFF00FF);
		for(int j = 0; j < 100; j++)
			for (int i = 0; i < 100; i++)
				my_mlx_pixel_put(vars->data_im, vars->pos.x + i, vars->pos.y
				+ j,0xF0FFF000);
//		my_mlx_pixel_put(vars->data_im, vars->pos.x, vars->pos.y,
//					 vars->pos.color);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data_im->img, 0, 0);
}

int main()
{
	void    *mlx;
	void	*mlx_win;

//	t_data	img;


//	mlx = mlx_init();
//	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//	img.img = mlx_new_image(mlx, 1920, 1080);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//								 &img.endian);
//
//	grad_line_top(&img, 0x990000, 200);
//	grad_line_top(&img, 0x004400, 200);
//	grad_line_top(&img, 0x00F000, 200);
//	grad_line_top(&img, 0xFF5700, 200);
//	grad_line_top(&img, 0xE0DB00, 200);

//	grad_line_top(&img, 0xFF570F, 200);
//	grad_line_top(&img, 0xFF57F0, 200);
//	grad_line_top(&img, 0xFF57FF, 200);

//	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//	mlx_loop(mlx);


	t_vars      vars;
	t_data		img;
//	pos_init(&vars.pos);

//	vars.mlx = mlx_init();
//	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
//	img.img = mlx_new_image(vars.mlx, 1920, 1080);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
//								 &img.endian);
//	vars.data_im = &img;
//	mlx_key_hook(vars.win, key_hook, &vars);
//	mlx_hook(vars.win, 2, 1L << 0, key_commands, &vars);
//	mlx_loop(vars.mlx);
	vars.mlx = mlx_init();
	pos_init(&vars.pos);
	vars.win = mlx_new_window(vars.mlx, RES_X, RES_Y, "Hello world!");
//	vars.data_im->img = mlx_new_image(vars.mlx, 1920, 1080);
//	img.img = mlx_new_image(vars.mlx, 1920, 1080);
//	vars.data_im = &img;
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_commands, &vars);
	mlx_loop(vars.mlx);


	return 0;
}
