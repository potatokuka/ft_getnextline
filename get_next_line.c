/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   og_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 11:34:21 by greed          #+#    #+#                */
/*   Updated: 2019/11/28 16:28:25 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int		pull_line(t_read *grab, char **line, int c)
{
	char			*temp;

	// perror("3");
	// printf("NL _%d_%d_\n", c, ft_strchr(*og, c));
	*line = ft_substr(grab, 0, ft_strchr(grab, c) - ((c == '\0') ? - 1 : + 1));
	// printf("LINE %s\n", *line);
	if (c == '\0')
	{
		free(grab->og);
		grab->og = NULL;
		//Free struct and remove from list
		return (0);
	}
	// printf("og STRCHR_%d_\n", ft_strchr(*og, c));
	// printf("og - og, C_%zu_\n", ft_strlen(*og));
	// printf("og b4 Temp_%s_\n", *og);
	// printf("_%s_", *og);
	temp = ft_substr(grab, ft_strchr(grab, c),
		grab->len - ft_strchr(grab, c));
	free(grab->og);
	grab->og = temp;
	// perror("4");
	// printf("_%s_\n", *og);
	// perror("6");
	return (1);
}

int		ft_strchr(t_read *grab, int c)
{
	size_t	i;

	i = 0;
	while (i < grab->len)
	{
		if (grab->og[i] == c)
			return (i + 1);
		i++;
	}
	if (!c)
		return (i);
	return (0);
}

char		*ft_substr(t_read *grab, unsigned int start, size_t sublen)
{
	char	*sub;

	if (!grab->og)
		return (NULL);
	if (grab->len < start)
		return (ft_strjoin("", ""));
	sub = (char*)malloc(sizeof(char) *
		((grab->len - start < sublen) ? grab->len - start : sublen) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, grab->og + start, ((grab->len - start < sublen) ? grab->len - start : sublen) + 1);
	return (sub);
}

char		*ft_strjoin(t_read *grab, char *s2, size_t readl)
{
	char	*res;
	size_t	i;

	if (!grab->og|| !s2)
		return (NULL);
	// perror("done");
	// printf("og_ %s\n", s1);
	// printf("HOLD_ %s\n", s2);
	res = (char*)malloc(sizeof(char) * (grab->len + readl + 1));
	if (!res)
		return (NULL);
	res[grab->len + readl] = '\0';
	i = 0;
	while (i < grab->len || i < readl)
	{
		if (i < grab->len)
			res[i] = grab->og[i];
		if (i < readl)
			res[i + grab->len] = s2[i];
		i++;
	}
	// printf("res_ %s\n", res);
	return (res);
}



int		get_next_line(int fd, char **line)
{
	static t_read		*get;
	int					has;
	t_read				*grab;
	
	grab = initiate_file(&get, fd);
	if (!grab->og)
	{
		grab->og = (char*)malloc(sizeof(char));
		grab->og[0] = '\0';
	}
	if (read(fd, 0, 0) == -1)
		return (-1);
	get_line(grab);
	// readl = 1;
	// while (readl && !ft_strchr(og, '\n'))
	// {
	// 	readl = read(fd, hold, BUFFER_SIZE);
	// 	hold[readl] = 0;
	// 	// perror("1");
	// 	// printf("og_ %s\n", og);
	// 	// printf("%s", hold);
	// 	// printf("PRE TEMP _%zu_%s_\n", readl, hold);
	// 	// this should make og until the new line
	// 	// perror("2");
	// 	tmp = ft_strjoin(og, hold);
	// 	// printf("TMP%s\n", tmp);
	// 	// printf("TEMP _%zu_%s_\n", readl, tmp);
	// 	free(og);
	// 	og = tmp;
	// 	// printf("BUF _%zu_%s_\n", readl, hold);
	// 	// printf("og _%d_%s-\n", ft_strchr(og, '\n'), og);
	// }
	// printf("\nREADSIZE _%zu_\n", readl);
	if (ft_strchr(grab, '\n') != -1)
		return (pull_line(&get, line, '\n'));
	else
		return (pull_line(&get, line, '\0'));
}

t_read	*initiate_file(t_read *get, int in_fd)
{
	t_read		*new_in;

	new_in = (t_read*)malloc(sizeof(t_read));
	while (get->next)
	{
		if (get->fd == in_fd)
			return (get);
		get = get->next;
	}
	if (get->fd == in_fd)
		return (get);
	get->next = new_in;
	new_in->len = 0;
	new_in->fd = in_fd;
	new_in->next = NULL;
	return (new_in);
}

void	get_line(t_read *grab)
{
	size_t		readl;
	char		*tmp;
	char		hold[BUFFER_SIZE + 1];
	readl = 1;
	while (readl && !ft_strchr(grab, '\n'))
	{
		readl = read(grab->fd, hold, BUFFER_SIZE);
		hold[readl] = '\0';
		// perror("1");
		// printf("og_ %s\n", og);
		// printf("%s", hold);
		// printf("PRE TEMP _%zu_%s_\n", readl, hold);
		// this should make og until the new line
		// perror("2");
		tmp = ft_strjoin(grab, hold, readl);
		grab->len += readl;
		free(grab->og);
		grab->og = tmp;
		// printf("TMP%s\n", tmp);
		// printf("TEMP _%zu_%s_\n", readl, tmp);
		// printf("BUF _%zu_%s_\n", readl, hold);
		// printf("og _%d_%s-\n", ft_strchr(og, '\n'), og);
	}
}