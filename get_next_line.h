/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 11:35:30 by greed          #+#    #+#                */
/*   Updated: 2019/11/29 22:13:04 by greed         ########   odam.nl         */
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
	struct s_read	*next;
}					t_read;

int		ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		get_next_line(int fd, char **line);
int		pull_line(char **get, char **line, int c);
t_read	*initiate_file(t_read **leave, int in_fd);
void	get_line(t_read *grab);
int		ft_freezer(t_read **get, t_read *grab);
#endif
