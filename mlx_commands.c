#include "hdrs/cub3d.h"

void ft_close (t_all *all)
{
	free_map(all->full_map);
	mlx_destroy_image(all->full_win->mlx,all->full_win->img);
	mlx_destroy_window(all->full_win->mlx, all->full_win->win);
//		free(all->full_win->win);
	exit (0);
}

void go_right(t_plr *plr)
{
	if (plr->ray.x < plr->x)
		plr->y += 10;
	if(plr->ray.angle > 3 * M_PI / 2)
		plr->x += 10;
//	else if (plr->ray.angle < M_PI)
//		plr->y -= 10;
//	else
//		plr->y += 10;
}

int			key_commands(int keycode, t_all *all)
{
	if (keycode == 65307)
		ft_close(all);
//	if (keycode == 3)
//		vars->pos.color = 0xFF0000;
//	if (keycode == 4)
//		vars->pos.color = 0x00FF00;
	else if (keycode == 100)
//		go_right(&all->plr);
		all->plr.x += STEP_Y;
	else if (keycode == 97)
		all->plr.x -= STEP_Y;
	else if (keycode == 119)
		all->plr.y -= STEP_Y;
	else if (keycode == 115)
		all->plr.y += STEP_Y;
	else if (keycode == 65361)
		all->plr.ray.angle -= 0.2;
	else if (keycode == 65363)
		all->plr.ray.angle += 0.2;

}
