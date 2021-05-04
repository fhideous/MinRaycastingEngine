#include "hdrs/cub3d.h"

void	head(int fd, t_all *all, int tmp, int file_size)
{
	char	header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(tmp);
	header[19] = (unsigned char)(tmp >> 8);
	header[20] = (unsigned char)(tmp >> 16);
	header[21] = (unsigned char)(tmp >> 24);
	tmp = -all->f_map->res.y;
	header[22] = (unsigned char)(tmp);
	header[23] = (unsigned char)(tmp >> 8);
	header[24] = (unsigned char)(tmp >>16);
	header[25] = (unsigned char)(tmp >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}

void	screenshot(t_all *all)
{
	int		fd;
	int		tmp;
	int		file_size;
	char	*print;

	fd = open("screenshot.bmp", O_CREAT | O_RDWR, 07777);
	if (fd < 0)
		message(16);
	tmp = all->f_map->res.x;
	file_size = 14 + 40 + (all->f_map->res.x * all->f_map->res.y) * 4;
	head(fd, all, tmp, file_size);
	print = (char *)all->f_w.addr;
	write(fd, print, (all->f_map->res.x * all->f_map->res.y * 4));
	close(fd);
	ft_close(all);
}
