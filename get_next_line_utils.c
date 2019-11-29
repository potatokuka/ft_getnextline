/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 11:35:44 by greed          #+#    #+#                */
/*   Updated: 2019/11/29 19:10:08 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "get_next_line.h"
#include <stdio.h>

char	*ft_strdup(char *s1)
{
	int				len;
	int				i;
	char			*str;

	len = 0;
	while (s1[len])
		len++;
	str = (char*)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t		ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	// printf("%zu", i);
	return (i);
}

size_t		ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	int i;

	if (!(src))
		return (0);
	i = 0;
	while (src[i] && i < (int)dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < (int)dstsize)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

int		ft_strchr(t_read *grab, int c)
{
	size_t	i;

	i = 0;
	// printf("GRAB LEN %zu_\n", grab->len);
	while (i < grab->len)
	{
		if (grab->og[i] == c)
			return (i);
		i++;
	}
	if (!c)
		return (i);
	return (-1);
}

char		*ft_substr(t_read *grab, unsigned int start, size_t sublen)
{
	char	*sub;

	if (!grab->og)
		return (NULL);
	if (grab->len < start)
		return (ft_strdup(""));
	sub = (char*)malloc(sizeof(char) *
		((grab->len - start < sublen) ? grab->len - start : sublen) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, grab->og + start, ((grab->len - start < sublen) ? grab->len - start : sublen) + 1);
	return (sub);
}
