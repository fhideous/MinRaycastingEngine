#include "hdrs/get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	j;
	unsigned int	k;
	char			*sj;

	if ((!s1) || (!s2))
		return (NULL);
	k = ft_strlen_gnl((char *)s1);
	j = ft_strlen_gnl((char *)s2);
	sj = (char *)(malloc(sizeof(char) * (k + j + 1)));
	if (!(sj))
		return (NULL);
	k = -1;
	while (s1[++k] != '\0')
		sj[k] = s1[k];
	j = -1;
	while (s2[++j] != '\0')
		sj[k + j] = s2[j];
	sj[j + k] = '\0';
	free((void *)s1);
	return (sj);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*su;

	i = 0;
	if (!s)
		return (NULL);
	su = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!(su))
		return (NULL);
	if (start >= ft_strlen_gnl((char *)s))
	{
		su[i] = '\0';
		return (su);
	}
	while (i < len)
	{
		su[i] = s[start + i];
		i++;
	}
	su[i] = '\0';
	return (su);
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		k;
	char	*str2;

	i = 0;
	k = 0;
	while (str[k] != '\0')
		k++;
	str2 = (char *)(malloc(sizeof(char) * (k + 1)));
	if (!str2)
		return (NULL);
	while (i != k)
	{
		str2[i] = str[i];
		i++;
	}
	str2[k] = '\0';
	return (str2);
}

int	ft_strchrr(char *str)
{
	int		i;
	char	c;

	c = '\n';
	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
