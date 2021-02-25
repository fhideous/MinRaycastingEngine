#include "hdrs/cub3d.h"
#include <math.h>

void            my_mlx_pixel_put(t_win *data, int x, int y,unsigned int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		add_plr(t_win *vars, t_all all)
{
	static int color = 0xFC69900;
	static int cnt = 0;
	static int i = 1;
	int			end_x;
	int			end_y;

	end_x = SCALE + all.plr.x ;
	end_y = SCALE + all.plr.y ;

//	scene_put(vars, 0xC6AC5B);
	for(int j = all.plr.x; j < end_x; j++)
		for (int i = all.plr.y; i < end_y; i++)
			my_mlx_pixel_put(vars, i, j, color);
	color += i;
	cnt += i;
	if (cnt == 255)
		i = -1;
	if(cnt == 0)
		i = 1;

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

int		add_ray(t_win *vars, t_all all)
{
	int color = 0xFF0000;

	for (int j = all.plr.y; j <= all.plr.ray.y; j++)
		for (int i = all.plr.x; i <= all.plr.ray.x; i++)
			my_mlx_pixel_put(vars, i + SCALE / 2, j + SCALE / 2, color);


	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

int		print_ray(t_win *vars, t_all all, double angle)
{
	int		color;
	float i;

	i = 0;
	color = 0x0000FF;
	while(i < all.plr.ray.len)
	{
		all.plr.ray.x = all.plr.x + i * cos(angle);
		all.plr.ray.y = all.plr.y + i * sin(angle);
		my_mlx_pixel_put(vars, all.plr.ray.y + SCALE / 2,
				   all.plr.ray.x + SCALE / 2, color);
		color -= 0x000006;
		i += 7;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}

int		wall_detect(t_ray ray, float *len, char **map)
{
	float det_x;
	float det_y;
	float i;
	int curr;

	int x;
	int y;

	i = 0;
	x = ray.x / SCALE;
//	ray.x -= 10.2;
	det_y = ray.y;
	while (1)
	{
//		curr = (int)ray.x;
		ray.y = ray.y + i;
//		if(curr < (int)ray.x)
		y = ray.y / SCALE;
			if (map[x][y] == '1')
				break;
		i += SCALE / 2;
	}
	det_x == ray.x * SCALE;
	i = 0;
	ray.y = det_y / SCALE;
	y = ray.y;
	while (1)
	{
//		curr = (int)ray.x;
		ray.x = ray.x + i;
//		if(curr < (int)ray.x)
		x = ray.x / SCALE;
		if (map[x][y] == '1')
			break;
		i += SCALE / 32;
	}
	det_y = ray.x;
	*len = sqrt(det_x * det_x + det_y * det_y);
}

int     render_next_frame(t_win *vars, t_all all)
{
	double angle;
	add_plr(vars, all);

	angle = all.plr.ray.angle - 30 / 57.3;
	while (angle <= 0 / 57.3)
	{
		all.plr.ray.x = all.plr.x + all.plr.ray.len * cos(angle);
		all.plr.ray.y = all.plr.y + all.plr.ray.len * sin(angle);
		angle += 0.01;
//		wall_detect(all.plr.ray, &all.plr.ray.len, all.map);
		print_ray(vars, all, angle);
	}
	add_ray(vars, all);
}

int	create_win(t_cub_map full_map, t_all all, t_win vars)
{

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, full_map.resolution.x,
						 full_map.resolution.y, "cub3d");
	vars.img = mlx_new_image(vars.mlx, full_map.resolution.x,
						  full_map.resolution.y);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
							   &vars.line_length, &vars.endian);
	render_next_frame(&vars, all);
//	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}