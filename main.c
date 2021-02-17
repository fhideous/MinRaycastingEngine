<<<<<<< HEAD
#include <stdio.h>
#include "hdrs/map_puuser.h"
#include <fcntl.h>
#include <stdlib.h>
#include "hdrs/cub3d.h"
#include "lib/libft.h"

void ss_free(char** mas)
{
	char **bn;

	bn = mas;
	while(mas && *mas)
	{
		free(*mas);
		*mas = NULL;
		mas++;
	}
	free(bn);
}

int main()
{
//	t_win      vars;
	char		**map;
	int i;
	char *path = "../map.noncub";
//	printf("HI");

	map	= get_map(path);

	i = -1;
	while (map[++i])
		ft_putendl_fd(map[i], 1);

	ss_free(map);
	return 0;
}
=======
>>>>>>> 2eeeae576b45b386bb47406825035d62fda8ec95
