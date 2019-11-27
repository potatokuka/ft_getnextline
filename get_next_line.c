/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 11:34:21 by greed          #+#    #+#                */
/*   Updated: 2019/11/27 16:49:23 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int		pull_line(char **get, char **line, int c)
{
	char			*temp;

	// printf("NL _%d_%d_\n", c, ft_strchr(*get, c));
	*line = ft_substr(*get, 0, ft_strchr(*get, c));
	if (c == '\0')
	{
		free(*get);
		return (0);
	}
	temp = ft_substr(*get, ft_strchr(*get, c) + 1,
		ft_strlen(*get, c) - ft_strchr(*get, c));
	free(*get);
	*get = temp;
	return (1);
}

int		ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	if (!c)
		return (i - 1);
	return (0);
}

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t				i;
	char				*dst;
	unsigned int		tmp;

	i = 0;
	if (!(s))
		return (NULL);
	tmp = ft_strchr(s, '\n');
	if (start > tmp)
		return (ft_strdup(""));
	dst = (char*)malloc(len + 1);
	if (!(dst))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		l1;
	int		l2;
	int		i;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	l1 = ft_strchr(s1, '\n');
	l2 = ft_strchr(s2, '\n');
	// printf("GET%s\n", s1);
	// printf("HOLD%s\n", s2);
	res = (char*)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!res)
		return (NULL);
	res[l1 + l2] = '\0';
	i = 0;
	while (i < l1 || i < l2)
	{
		if (i < l1)
			res[i] = s1[i];
		if (i < l2)
			res[i + l1] = s2[i];
		i++;
	}
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char			*get;
	char				*tmp;
	char				hold[BUFFER_SIZE];
	size_t				readl;
	int					has;

	has = 0;
	if (!get)
	{
		get = (char*)malloc(sizeof(char));
		get[0] = '\0';
	}
	readl = 1;
	while (readl /* && !ft_strchr(get, '\n')*/)
	{
		readl = read(fd, hold, BUFFER_SIZE - 1);
		hold[readl] = 0;
		printf("%s", hold);
		if (!readl)
			break ;
		// printf("PRE TEMP _%zu_%s_\n", readl, hold);
		tmp = ft_strjoin(get, hold);
		// printf("TMP%s\n", tmp);
		// printf("TEMP _%zu_%s_\n", readl, tmp);
		free(get);
		get = tmp;
		// printf("BUF _%zu_%s_\n", readl, hold);
		// printf("GET _%d_%s-\n", ft_strchr(get, '\n'), get);
	}
	// printf("\nREADSIZE _%zu_\n", readl);
	if (readl)
		return (pull_line(&get, line, '\n'));
	else
		return (pull_line(&get, line, '\0'));
}
