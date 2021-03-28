#include "hdrs/cub3d.h"

//void put_n_pixel(t_all *vars, int i, int j, int n, unsigned int color)
//{
//	int it;
//	int jt;
//
//	it = -1;
//	jt = -1;
//	while (++it < n )
//	{
//		while (++jt < n)
//			my_mlx_pixel_put(vars->full_win, jt + i * SCALE / 4,
//							 it + j * SCALE / 4, color);
//		jt = -1;
//	}
//}

//void 		scene_put(t_all *vars, t_cub_map *full_map)
//{
////	struct n_map *start;
//	char **start;
//	int i;
//	int j;
//	int n;
//
//	i = 0;
//	j = 0;
//	start = vars->full_map->map;
//	while (start && (*start))
//	{
//		while (**(start))
//		{
//			if(**(start) == '1')
//				put_n_pixel(vars,i, j, SCALE / 4,0xE3CC87);
//			if (**(start) == '2')
//				put_n_pixel(vars,i, j, SCALE / 4, 0xF0958659);
//			if(**(start) == '0')
//				put_n_pixel(vars,i, j, SCALE / 4, 0xF0958659);
////			if (*(vars->map->line) == 'N')
////				put_n_pixel(vars,i, j, n, 0xE3D29F);
//			i += 1;
//			(*start)++;
//		}
//		(*start) -= i;
//		i = 0;
//		j++;
//		start++;
////		vars->map = vars->map->n;
//	}
//	start -= j;
////	vars->map = start;
//	mlx_put_image_to_window(vars->full_win->mlx,
//							vars->full_win->win, vars->full_win->img, 0, 0);
//}