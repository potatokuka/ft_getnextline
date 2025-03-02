/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/01 15:20:08 by greed          #+#    #+#                */
/*   Updated: 2019/12/01 15:20:19 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "get_next_line_bonus.h"

char		*ft_strdup(char *s1)
{
	unsigned char	*block;
	int				len;
	int				i;
	char			*str;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	block = (unsigned char*)malloc(len + 1);
	if (!(block))
		ENOMEM;
	else
	{
		str = (char*)malloc(len + 1);
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (0);
}

size_t		ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t		ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	int i;

	i = 0;
	if (!(src))
		return (0);
	while (src[i] && i < (int)dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
