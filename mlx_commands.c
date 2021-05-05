#include "hdrs/cub3d.h"

int	ft_close(t_all *all)
{
	free_map(all->f_map);
	mlx_destroy_image(all->f_w.mlx, all->f_w.img);
	mlx_destroy_window(all->f_w.mlx, all->f_w.win);
	mlx_destroy_image(all->f_w.mlx, all->ts.spite.img_tmp);
	mlx_destroy_image(all->f_w.mlx, all->ts.w_tex.img_tmp);
	mlx_destroy_image(all->f_w.mlx, all->ts.n_tex.img_tmp);
	mlx_destroy_image(all->f_w.mlx, all->ts.e_tex.img_tmp);
	mlx_destroy_image(all->f_w.mlx, all->ts.s_tex.img_tmp);
	exit (250);
}

void	check_crossing(t_plr *plr, t_all *all, int is_x)
{
	float	left_len;
	float	right_len;
	float	center_len;

	find_crossing(all, all->plr.ray.angle
		- (M_PI_12 + M_PI_12), -1, &all->ts.n_tex);
	left_len = all->plr.ray.len;
	find_crossing(all, all->plr.ray.angle
		+ (M_PI_12 + M_PI_12), -1, &all->ts.n_tex);
	right_len = all->plr.ray.len;
	find_crossing(all, all->plr.ray.angle, -1, &all->ts.n_tex);
	center_len = all->plr.ray.len;
	if (right_len <= 1 || left_len <= 1
		|| ((int)center_len <= (1)))
	{
		if (is_x == 1 || is_x == -1)
			plr->x -= (float)is_x * SPEED_X;
		else
			plr->y -= (float)is_x * SPEED_Y / 2;
	}
}

int	key_commands(int keycode, t_all *all)
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
