#include "hdrs/cub3d.h"

int	render_next_frame(t_all *all)
{
	add_flour(all);
	add_ray(all, &all->f_map->res,
		(float)all->f_map->res.x
		/ (float)all->f_map->res.y);
	distance_to_sprites(all);
	sprite_sort(all->spr_loc, all->s_spr);
	find_angle_sprite(all);
	print_sprite(all);
	do_kek(all);
}

int	create_win(t_all *all)
{
	all->f_w.win = mlx_new_window(all->f_w.mlx,
			 all->f_map->res.x,
			 all->f_map->res.y, "cub3d");
	all->f_w.img = mlx_new_image(all->f_w.mlx,
			all->f_map->res.x, all->f_map->res.y);
	all->f_w.addr = (unsigned int *)mlx_get_data_addr(all->f_w.img,
			&all->f_w.BPP,
			&all->f_w.l_len,
			&all->f_w.endian);
//	mlx_hook(all->f_w.win, 17, 1L << 17, ft_close, all);
	mlx_hook(all->f_w.win, 2, 1L << 0, key_commands, all);
	if (all->screen)
	{
		render_next_frame(all);
		screenshot(all);
	}
	mlx_loop_hook(all->f_w.mlx, render_next_frame, &all->f_w);
//	ft_close(all);
	mlx_loop(all->f_w.mlx);
}
