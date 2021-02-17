/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhideous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:45:00 by fhideous          #+#    #+#             */
/*   Updated: 2020/11/29 17:45:04 by fhideous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 12
//#endif
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		get_next_line(int fd, char **line);

#endif