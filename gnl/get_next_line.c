/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhideous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:25:55 by fhideous          #+#    #+#             */
/*   Updated: 2020/12/02 17:25:57 by fhideous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int             find_transl(const char *str)
{
	int i;

	if (!str)
		return (-1);
	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int             add_line(char **line, char **donor, int n)
{
	char	*tmp;
	char	*new_rmd;
	int		i;

	if (n < 0)
		return (0);
	if (!(tmp = ft_calloc(n + 1, sizeof(char))))
		return (-1);
	i = -1;
	while (++i < n)
		tmp[i] = *((*donor) + i);
	*line = tmp;
	if (!*donor)
		return (1);
	if (!(new_rmd = ft_substr(*donor, n + 1, ft_strlen(*donor) - n - 1)))
		return (-1);
	free(*donor);
	*donor = new_rmd;
	return (1);
}

static int		read_buf(int fd, char **rmd)
{
	int		count;
	char	*buf_rd;
	char	*joined;

	if (!(buf_rd = ft_calloc(BUFFER_SIZE + 1, sizeof(char))))
		return (-1);
	if ((count = read(fd, buf_rd, BUFFER_SIZE)) <= 0)
		free(buf_rd);
	if (count < 0)
		return (-1);
	else if (count == 0)
		return (0);
	if (!(joined = ft_strjoin(*rmd, buf_rd)))
		return (-1);
	free(buf_rd);
	free(*rmd);
	*rmd = joined;
	return (1);
}

static void     ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

int             get_next_line(int fd, char **line)
{
	static char	*rem;
	int			is_tr;
	int			count;
	static int	is_first;

	count = 1;
	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	while (count != 0)
	{
		if ((is_tr = add_line(&*line, &rem, find_transl(rem))) == -1)
			return (-1);
		if (is_tr == 1)
			return (1);
		if ((count = read_buf(fd, &rem)) == -1)
			return (-1);
	}
	if (!is_first)
		*line = "\0";
	if (!*line && (!rem || !*rem) && is_first++)
		return (0);
	if ((add_line(&*line, &rem, ft_strlen(rem))) == -1)
		return (-1);
	ft_free(&rem);
	return (0);
}
