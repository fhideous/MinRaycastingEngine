#include "hdrs/cub3d.h"

void ft_close (t_all *all)
{
	free_map(all->full_map);
	mlx_destroy_image(all->full_win->mlx,all->full_win->img);
	mlx_destroy_window(all->full_win->mlx, all->full_win->win);

	mlx_destroy_image(all->full_win->mlx, all->textrs.spite.img_tmp);
	mlx_destroy_image(all->full_win->mlx, all->textrs.w_tex.img_tmp);
	mlx_destroy_image(all->full_win->mlx, all->textrs.n_tex.img_tmp);
	mlx_destroy_image(all->full_win->mlx, all->textrs.e_tex.img_tmp);
	mlx_destroy_image(all->full_win->mlx, all->textrs.s_tex.img_tmp);
	free(all->full_win);

	exit (0);
}

void check_crossing(t_plr *plr, char **map)
{
	float x_plr;
	float y_plr;

//	x_plr = plr->x / SCALE;
//	y_plr = plr->y / SCALE;
//	printf("x: %d\n",x_plr);
//	printf("x: %d\n",y_plr);
//	if (map[(int)y_plr][(int)x_plr] == '1')
//	{
//		plr->x -= 10 *SPEED_X;
//		plr->y -= 10 * SPEED_Y;
//	}
}

void go_right(t_plr *plr, t_cub_map *map)
{
	if (plr->ray.angle <= M_PI_4)
		plr->y += SPEED_Y;
	else if (plr->ray.angle <= 3 * M_PI_4)
		plr->x -= SPEED_X;
	else if (plr->ray.angle <= 5 * M_PI_4)
		plr->y -= SPEED_Y;
	else if (plr->ray.angle <= 7* M_PI_4)
		plr->x += SPEED_X;
	else
		plr->y += SPEED_Y;
	check_crossing(plr, map->map);
}

void go_left(t_plr *plr, t_cub_map *map)
{
	if (plr->ray.angle <= M_PI_4)
		plr->y -= SPEED_Y;
	else if (plr->ray.angle <= 3 * M_PI_4)
		plr->x += SPEED_X;
	else if (plr->ray.angle <= 5 * M_PI_4)
		plr->y += SPEED_Y;
	else if (plr->ray.angle <= 7* M_PI_4)
		plr->x -= SPEED_X;
	else
		plr->y -= SPEED_Y;
	check_crossing(plr, map->map);
}

void go_back(t_plr *plr, t_cub_map *map)
{
	if (plr->ray.angle <= M_PI_4)
		plr->x += SPEED_Y;
	else if (plr->ray.angle <= 3 * M_PI_4)
		plr->y += SPEED_X;
	else if (plr->ray.angle <= 5 * M_PI_4)
		plr->x -= SPEED_Y;
	else if (plr->ray.angle <= 7* M_PI_4)
		plr->y -= SPEED_X;
	else
		plr->x += SPEED_Y;
	check_crossing(plr, map->map);
}

void go_forward(t_plr *plr, t_cub_map *map)
{
	if (plr->ray.angle <= M_PI_4)
		plr->x -= SPEED_Y;
	else if (plr->ray.angle <= 3 * M_PI_4)
		plr->y -= SPEED_X;
	else if (plr->ray.angle <= 5 * M_PI_4)
		plr->x += SPEED_Y;
	else if (plr->ray.angle <= 7* M_PI_4)
		plr->y += SPEED_X;
	else
		plr->x -= SPEED_Y;
	check_crossing(plr, map->map);
}

void change_angle(t_ray *ray, float value)
{
	ray->angle += value;
	if (ray->angle > M_PI * 2)
		ray->angle -= M_PI * 2;
	if (ray->angle < 0)
		ray->angle += M_PI * 2;
}


int			key_commands(int keycode, t_all *all)
{
	if (keycode == 65307)
		ft_close(all);
	else if (keycode == 100)
		go_right(&all->plr, all->full_map);
	else if (keycode == 97)
		go_left(&all->plr, all->full_map);
	else if (keycode == 119)
		go_back(&all->plr, all->full_map);
	else if (keycode == 115)
		go_forward(&all->plr, all->full_map);
	else if (keycode == 65361)
		change_angle(&all->plr.ray, -ROTATE_SPEED);
	else if (keycode == 65363)
		change_angle(&all->plr.ray, ROTATE_SPEED);


}
