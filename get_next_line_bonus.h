/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:44 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/05 00:52:30 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef	struct		s_gnl
{
	int				fd;
	char			*content;
	struct s_gnl	*first;
	struct s_gnl	*next;
}					t_gnl;

t_gnl				*get_fd(int fd, t_gnl *fd_content);
int					ft_strlen(char *str);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncpy(char *dest, char *src, int n);
char				*ft_strnew(int size);
int					get_next_line(int fd, char **line);
t_gnl				*get_fd_content(int fd, t_gnl *fd_content);
char				*ft_strncat(char *dest, char *src, unsigned int nb);

#endif
