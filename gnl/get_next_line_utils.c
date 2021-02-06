/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhideous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:22:58 by fhideous          #+#    #+#             */
/*   Updated: 2020/12/02 17:23:01 by fhideous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
    void	*ptr;
	char	*s;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	s = (char *)ptr;
	while (count--)
		*s++ = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*(s + cnt) != '\0')
		cnt++;
	return (cnt);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char			*ptr;
	const unsigned char		*src_ptr;

	if (dst == NULL && src == NULL)
		return (0);
	ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	while (len--)
		*ptr++ = *src_ptr++;
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc_str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	conc_str = (char *)malloc(s1_len + s2_len + 1);
	if (!conc_str)
		return (NULL);
	ft_memcpy(conc_str, s1, s1_len);
	ft_memcpy(conc_str + s1_len, s2, s2_len);
	*(conc_str + s1_len + s2_len) = '\0';
	return (conc_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		start = 0;
		len = 0;
	}
	sub_str = (char *)malloc(len + 1);
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s + start, len);
	*(sub_str + len) = '\0';
	return (sub_str);
}
