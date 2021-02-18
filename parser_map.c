#include <stdio.h>
#include <fcntl.h>
//#include "hdrs/get_next_line.h"
#include "hdrs/map_puuser.h"
#include "stdlib.h"
#include "lib/libft.h"

void del_f(void *ch)
{
	free(ch);
	ch = NULL;
}


/*
 * map parsing
 */

static char	**list_to_massive(t_list **hd, size_t len)
{
	char	  **map;
	int		  i;
	t_list	*tmp;
	t_list	*old;

	if (!(map = ft_calloc(len + 1, sizeof(char *))))
		return (NULL);
	tmp = *hd;
	i = -1;
	while (len--)
	{
		old = tmp;
		map[++i] = tmp->data;
		tmp = tmp->next;
		free(old);
	}
	return (map);
}

/*
 * line приходит из parse_set
 */

char		**get_map(int fd, char *line)
{
	t_list	*hd;
	char	**map;

	hd = NULL;
	if (line)
		ft_lstadd_back(&hd, ft_lstnew(line));
	while (get_next_line(fd, &line) == 1)
		ft_lstadd_back(&hd, ft_lstnew(line));
	ft_lstadd_back(&hd, ft_lstnew(line));
	map = list_to_massive(&hd, ft_lstsize(hd));
	return (map);
}
