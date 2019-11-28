/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 11:35:30 by greed          #+#    #+#                */
/*   Updated: 2019/11/28 18:05:17 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct		s_read
{
	char			*og;
	size_t			len;
	int				fd;
	struct s_read	*next
}					t_read;

int		ft_strchr(t_read *g, int c);
char	*ft_strdup(char *src);
size_t	ft_strlen(char *s);
char	*ft_substr(t_read *grab, unsigned int start, size_t sublen);
char	*ft_strjoin(t_read *grab, char *s2, size_t readl);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		get_next_line(int fd, char **line);
int		pull_line(t_read *grab, char **line, int c);
#endif
