/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/29 20:39:13 by greed          #+#    #+#                */
/*   Updated: 2019/11/29 20:39:22 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int		ft_freezer(t_read **get, t_read *grab)
{
	t_read		*move;
	// perror("EOF free res");
	free(grab->og);
	grab->og = NULL;
	// printf("MOVE_%zu_", move->next);
	if (*get == grab)
	{
		// perror("new1st");
		*get = grab->next;
	}
	else
	{
		// perror("move next");
		move = *get;
		while (move && move->next != grab)
		{
			move = move->next;
			// perror("am im here?");
			move->next = grab->next;
		}
	}
	// perror("free fin");
	free(grab);
	grab = NULL;
	return (0);
}

int		pull_line(t_read **get, t_read *grab, char **line, int c)
{
	char			*tmp;

	// perror("3");
	if (line && *line)
		free(*line);
	*line = ft_substr(grab, 0, ft_strchr(grab, c));
	// printf("LINE %s\n", *line);
	if (c == '\0')
	{
		// perror("the shitshow starts here");
		return(ft_freezer(get, grab));
	}
	tmp = ft_substr(grab, ft_strchr(grab, c) +1,
		grab->len - ft_strchr(grab, c));
	grab->len -= ft_strchr(grab, c) + 1;
	free(grab->og);
	grab->og = tmp;
	return (1);
}

char		*ft_strjoin(t_read *grab, char *s2, size_t readl)
{
	char	*res;
	size_t	i;

	if (!grab->og || !s2)
		return (NULL);
	res = (char*)malloc(sizeof(char) * (grab->len + readl + 1));
	if (!res)
		return (NULL);
	res[grab->len + readl] = '\0';
	i = 0;
	// printf("strjoin GRAB_len_ %d\n", grab->len);
	// printf("strjoin readl value_ %d\n", readl);
	while (i < grab->len || i < readl)
	{
		if (i < grab->len)
			res[i] = grab->og[i];
		if (i < readl)
			res[i + grab->len] = s2[i];
		i++;
	}
	// printf("res_ %s\n", res);
	// printf("RES HOLD__ %s\n", s2);
	return (res);
}


void	get_line(t_read *grab)
{
	size_t		readl;
	char		*tmp;
	char		hold[BUFFER_SIZE];

	readl = 1;
	while (readl && ft_strchr(grab, '\n') == -1)
	{
		readl = read(grab->fd, hold, BUFFER_SIZE);
		// printf("HOLD_%d_%s_\n", readl, hold);
		// hold[readl] = '\0';
		// perror("2");
		tmp = ft_strjoin(grab, hold, readl);
		grab->len += readl;
		free(grab->og);
		grab->og = tmp;
		// printf("OG %s_\n", grab->og);
	}
}

t_read	*initiate_file(t_read **leave, int in_fd)
{
	t_read		*new_in;
	t_read		*get;

	get = *leave;
	while (get && get->next)
	{
		if (get->fd == in_fd)
			return get;
		get = get->next;
	}
	if (get && get->fd == in_fd)
		return (get);
	new_in = (t_read*)malloc(sizeof(t_read));
	if (*leave)
		get->next = new_in;
	new_in->len = 0;
	new_in->fd = in_fd;
	new_in->next = NULL;
	new_in->og = (char*)malloc(sizeof(char));
	new_in->og[0] = '\0';
	return (new_in);
}

int		get_next_line(int fd, char **line)
{
	static t_read		*get;
	t_read				*grab;
	
	grab = initiate_file(&get, fd);
	// if (!grab->og)
	// {
	// 	grab->og = (char*)malloc(sizeof(char));
	// 	grab->og[0] = '\0';
	// }
	if (read(fd, 0, 0) == -1)
		return (-1);
	get_line(grab);
	if (ft_strchr(grab, '\n') != -1)
		return (pull_line(&get, grab, line, '\n'));
	else
	{
		// perror("666");
		return (pull_line(&get, grab, line, '\0'));
	}
}

// it's missing the second to last line