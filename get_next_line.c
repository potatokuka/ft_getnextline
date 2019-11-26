/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 11:34:21 by greed          #+#    #+#                */
/*   Updated: 2019/11/26 18:45:45 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

// read at fd, malloc buff size + 1
// read FD until '\n', store the pointer from the end
// set tmp point to a, b is the char after the new line
// keep reading until the end of the file?

int		pull_line(char *get, char **line, int c)
{
	char			*temp;

	printf("NL _%d_%zu_\n", c, ft_strchr(get, c));
	*line = ft_substr(get, 0, ft_strchr(get, c));
	if (c == '\0')
	{
		free(get);
		return (0);
	}
	temp = ft_substr(get, ft_strchr(get, c) + 1,
		ft_strlen(get) - ft_strchr(get, c));
	free(get);
	get = temp;
	return (1);
}
//  strjoin & strdup
// substr

// int		*ft_strchr(char *s, int c)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char*)&s[i]);
// 		i++;
// 	}
// 	if (s[i] == (char)(c))
// 		return ((char*)&s[i]);
// 	return (NULL);
// }
int		ft_strchr(char *s, int c)
{
	size_t	i;
	printf("INSIDE ME");
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (!c)
		return (i);
	return (0);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	char				*dst;
	unsigned int		tmp;

	i = 0;
	if (!(s))
		return (NULL);
	tmp = ft_strlen(s);
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
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
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
	static char 		*get;
	char 				*tmp;
	char 				*hold[BUFFER_SIZE];
	size_t				readsize;

	if (!get)
	{
		get = (char*)malloc(sizeof(BUFFER_SIZE) + 1);
		get[0] = '\0';
		// ft_strdup src into dst?
		// move temp point to the start of original src start point
	}
	readsize = 1;
	printf("DONE");
	while (readsize && !ft_strchr(get, '\n'))
	{
		readsize = read(fd, hold, BUFFER_SIZE - 1);
		hold[readsize] = '\0';
		if (!readsize)
			break ;
		tmp = ft_strjoin(get, hold);
		free(get);
		get = tmp;
		printf("BUF _%zu_%s_\n", readsize, hold);
		printf("GET _%d_%s-\n", ft_strchr(get, '\n'), get);
		printf("DONE");
	}
	printf("\nREADSIZE _%zu_\n", readsize);
	if (readsize)
		return (pull_line(get, line, '\n'));
	else
		return (pull_line(get, line, '\0'));
}
