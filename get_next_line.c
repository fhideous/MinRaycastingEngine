#include "hdrs/get_next_line.h"
#include "lib/libft.h"
static char	*ft_begin(const char *s)
{
	char	*s1;
	int		last;

	last = 0;
	if (s[last] == '\n' || s[last] == '\0')
		return (ft_strdup(""));
	else
		while (*s && s[last] != '\0' && s[last] != '\n')
			last++;
	s1 = ft_substr(s, 0, last);
	return (s1);
}

static char	*ft_end(char *s)
{
	char	*s1;
	int		last;

	last = 0;
	while (s[last] != '\n' && s[last] != '\0')
		last++;
	if (s[last] == '\0')
	{
		free(s);
		return (0);
	}
	s1 = ft_substr(s, last + 1, ft_strlen_gnl((char *)s) - last);
	free(s);
	return (s1);
}

static int	save(char **ost, char **line, int byte)
{
	*line = ft_begin(*ost);
	*ost = ft_end(*ost);
	while (ft_strchrr(*ost) && (byte == 0))
		return (1);
	if (byte == 0)
		return (0);
	else
		return (1);
}

static int	readfile(int fd, char *buf, char **ost, char **line)
{
	int		reading_byte;

	if (!(*ost))
		*ost = ft_strdup("");
	reading_byte = 1;
	while (!(ft_strchrr(*ost)) && ((reading_byte != 0)))
	{
		reading_byte = read(fd, buf, BUFFER_SIZE);
		if (reading_byte == -1)
		{
			free(*ost);
			*ost = NULL;
			return (-1);
		}
		buf[reading_byte] = '\0';
		*ost = ft_strjoin(*ost, buf);
	}
	free(buf);
	return (save(&*ost, line, reading_byte));
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*ost;

	if ((fd < 0) || (!(line)) || (BUFFER_SIZE <= 0))
		return (-1);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!(buf))
		return (-1);
	return (readfile(fd, buf, &ost, line));
}
