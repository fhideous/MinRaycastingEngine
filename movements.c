#include "hdrs/cub3d.h"

void	go_right(t_plr *plr, t_all *all)
{
	int	is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = 2;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = -1;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = -2;
	else if (plr->ray.angle <= 7 * M_PI_4)
		is_x = 1;
	else
		is_x = 2;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void	go_left(t_plr *plr, t_all *all)
{
	int	is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = -2;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = 1;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = 2;
	else if (plr ->ray.angle <= 7 * M_PI_4)
		is_x = -1;
	else
		is_x = -2;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void	go_back(t_plr *plr, t_all *all)
{
	int	is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = 1;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = 2;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = -1;
	else if (plr->ray.angle <= 7 * M_PI_4)
		is_x = -2;
	else
		is_x = 1;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void	go_forward(t_plr *plr, t_all *all)
{
	int	is_x;

	if (plr->ray.angle <= M_PI_4)
		is_x = -1;
	else if (plr->ray.angle <= 3 * M_PI_4)
		is_x = -2;
	else if (plr->ray.angle <= 5 * M_PI_4)
		is_x = 1;
	else if (plr->ray.angle <= 7 * M_PI_4)
		is_x = 2;
	else
		is_x = -1;
	if (is_x == 1 || is_x == -1)
		plr->x += is_x * SPEED_X;
	else
		plr->y += is_x / 2 * SPEED_Y;
	check_crossing(plr, all, is_x);
}

void	change_angle(t_all *all, float value)
{
	float	right_len;
	float	left_len;

	all->plr.ray.angle += (value + value);
	if (all->plr.ray.angle >= M_PI + M_PI)
		all->plr.ray.angle -= (M_PI + M_PI);
	else if (all->plr.ray.angle <= 0)
		all->plr.ray.angle += (M_PI + M_PI);
	find_crossing(all, all->plr.ray.angle + M_PI_6, -1, &all->textrs.n_tex);
	right_len = all->plr.ray.len;
	find_crossing(all, all->plr.ray.angle - M_PI_6, -1, &all->textrs.n_tex);
	left_len = all->plr.ray.len;
	if (right_len < all->textrs.n_tex.width >> 1
		|| left_len < all->textrs.n_tex.width >> 1)
		all->plr.ray.angle -= (value + value);
	else
		all->plr.ray.angle -= value;
}
