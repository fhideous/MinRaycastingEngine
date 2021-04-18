#include "hdrs/cub3d.h"

void ft_close (t_all *all)
{
	free_map(all->full_map);
	mlx_destroy_image(all->full_win.mlx,all->full_win.img);
	mlx_destroy_window(all->full_win.mlx, all->full_win.win);

	mlx_destroy_image(all->full_win.mlx, all->textrs.spite.img_tmp);
	mlx_destroy_image(all->full_win.mlx, all->textrs.w_tex.img_tmp);
	mlx_destroy_image(all->full_win.mlx, all->textrs.n_tex.img_tmp);
	mlx_destroy_image(all->full_win.mlx, all->textrs.e_tex.img_tmp);
	mlx_destroy_image(all->full_win.mlx, all->textrs.s_tex.img_tmp);
//	free(all->full_win);

	exit (250);
}

void check_crossing(t_plr *plr, t_all *all, int is_x)
{
	float left_len;
	float right_len;
	float center_len;
	int		x_y;

//	x_plr = plr->x / SCALE;
//	y_plr = plr->y / SCALE;
//	printf("x: %d\n",x_plr);
//	printf("x: %d\n",y_plr);
//	if (map[(int)y_plr][(int)x_plr] == '1')
//	{
//		plr->x -= 10 *SPEED_X;
//		plr->y -= 10 * SPEED_Y;
//	}
	find_crossing(all, all->plr.ray.angle - (M_PI_12 /*+ M_PI_12*/), &all->full_win, &all->textrs.n_tex);
	left_len = all->plr.ray.len;
	find_crossing(all, all->plr.ray.angle + (M_PI_12 /*+ M_PI_12*/), &all->full_win, &all->textrs.n_tex);
	right_len = all->plr.ray.len;
	find_crossing(all, all->plr.ray.angle, &all->full_win, &all->textrs.n_tex);
	center_len = all->plr.ray.len;
	x_y = all->full_map->resolution.y /  all->full_map->resolution.x;
	if (right_len <= all->textrs.n_tex.width >> (2 * x_y) || left_len <= all->textrs.n_tex.width >> (2 * x_y)
	||  ((int)center_len <= (all->textrs.n_tex.width >> ( x_y))))
	{
		if (is_x == 1 || is_x == -1)
			plr->x -= is_x * SPEED_X;
		else
			plr->y -= is_x * SPEED_Y / 2;
	}
}

void go_right(t_plr *plr, t_all *all)
{
	int is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = 2;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = -1;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = -2;
	else if (plr->ray.angle <= 7* M_PI_4)
		is_x = 1;
	else
		is_x = 2;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void go_left(t_plr *plr, t_all *all)
{
	int is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = -2;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = 1;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = 2;
	else if (plr ->ray.angle <= 7* M_PI_4)
		is_x = -1;
	else
		is_x = -2;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void go_back(t_plr *plr, t_all *all)
{
	int is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = 1;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = 2;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = -1;
	else if (plr->ray.angle <= 7* M_PI_4)
		is_x = -2;
	else
		is_x = 1;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void go_forward(t_plr *plr, t_all *all)
{
	int is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = -1;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = -2;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = 1;
	else if (plr->ray.angle <= 7* M_PI_4)
		is_x = 2;
	else
		is_x = -1;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;

	check_crossing(plr, all, is_x);
}

void change_angle(t_all *all, float value)
{
	float right_len;
	float left_len;
	all->plr.ray.angle +=  (value + value);
	if (all->plr.ray.angle >= M_PI + M_PI) {
		all->plr.ray.angle -= (M_PI + M_PI);
	}
	else if (all->plr.ray.angle <= 0) {
		all->plr.ray.angle += (M_PI + M_PI);
	}
	find_crossing(all, all->plr.ray.angle + M_PI_6, &all->full_win, &all->textrs.n_tex);
	right_len =  all->plr.ray.len;
	find_crossing(all, all->plr.ray.angle - M_PI_6, &all->full_win, &all->textrs.n_tex);
	left_len = all->plr.ray.len;
	if (right_len < all->textrs.n_tex.width >> 1
		|| left_len < all->textrs.n_tex.width >> 1)
		all->plr.ray.angle -=  (value + value);
	else all->plr.ray.angle -= value;

}


int			key_commands(int keycode, t_all *all)
{
	if (keycode == 65307)
		ft_close(all);
	else if (keycode == 100)
		go_right(&all->plr, all);
	else if (keycode == 97)
		go_left(&all->plr, all);
	else if (keycode == 119)
		go_back(&all->plr, all);
	else if (keycode == 115)
		go_forward(&all->plr, all);
	else if (keycode == 65361)
		change_angle(all, -ROTATE_SPEED);
	else if (keycode == 65363)
		change_angle(all, ROTATE_SPEED);


}
