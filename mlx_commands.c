#include "hdrs/cub3d.h"

int             key_commands(int keycode, t_all *all)
{
	if (keycode == 65307)
		mlx_destroy_window(all->full_win->mlx, all->full_win->win);
//	if (keycode == 3)
//		vars->pos.color = 0xFF0000;
//	if (keycode == 4)
//		vars->pos.color = 0x00FF00;
	if (keycode == 100)
		all->plr.x += 10;
	if (keycode == 97)
		all->plr.x -= 10;
	if (keycode == 119)
		all->plr.y -= 10;
	if (keycode == 115)
		all->plr.y += 10;
	if (keycode == 65363)
		all->plr.ray.angle -= 0.1;
	if (keycode == 65361)
		all->plr.ray.angle += 0.1;

}
