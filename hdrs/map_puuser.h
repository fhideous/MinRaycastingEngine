#ifndef CUB3D_MAP_PUUSER_H
#define CUB3D_MAP_PUUSER_H

struct n_map
{
	char			*line;
	struct n_map	*n;
} t_map;

void *get_map(int fd);

#endif //CUB3D_MAP_PUUSER_H
