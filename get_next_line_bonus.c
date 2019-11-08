/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/04 03:38:18 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			no_newline_in_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (0);
	return (1);
}

static int			get_content_from_file(int fd, t_gnl *ptr)
{
	int		nb_read;
	char	*s;
	char	*buff;

	if (!(buff = ft_strnew(BUFFER_SIZE + 1)))
		return (-1);
	if ((nb_read = read(fd, buff, BUFFER_SIZE)) <= 0)
	{
		free(buff);
		return (nb_read);
	}
	buff[nb_read] = '\0';
	if (!(s = ft_strnew(ft_strlen(ptr->content) + nb_read + 1)))
		return (-1);
	if (ptr->content)
	{
		s = ft_strncat(s, ptr->content, ft_strlen(ptr->content));
		free(ptr->content);
	}
	ptr->content = ft_strncat(s, buff, nb_read);
	free(buff);
	if (no_newline_in_str(ptr->content))
		return (get_content_from_file(fd, ptr));
	return (1);
}

static int			extract_line(char **line, char **str, int *i, int *j)
{
	char	*s;
	char	*s1;
	char	*tmp;

	while ((*str)[*i] && (*str)[*i] != '\n')
		(*i)++;
	if (!(s = ft_strnew(*i + 1)))
		return (-1);
	*line = ft_strncat(s, *str, *i);
	*j = ft_strlen(*str) - *i;
	if (!*j)
	{
		free(*str);
		*str = ft_strnew(1);
		return (0);
	}
	if ((s1 = ft_strnew(*j)))
	{
		tmp = ft_strncat(s1, *str + *i + 1, *j - 1);
		free(*str);
		*str = tmp;
		return (1);
	}
	return (-1);
}

static int			manage_str(t_gnl **fd_content, char **line)
{
	int res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = 0;
	if ((res = extract_line(line, &((*fd_content)->content), &i, &j) != 1))
	{
		if (res == -1)
		{
			*fd_content = (*fd_content)->first;
			return (-1);
		}
		*fd_content = (*fd_content)->first;
		return (0);
	}
	*fd_content = (*fd_content)->first;
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_gnl *fd_content = NULL;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	fd_content = get_fd(fd, fd_content);
	if (no_newline_in_str(fd_content->content))
	{
		if (get_content_from_file(fd, fd_content) == -1)
		{
			fd_content = fd_content->first;
			return (-1);
		}
		if (!fd_content->content)
		{
			*line = ft_strnew(1);
			fd_content = fd_content->first;
			return (0);
		}
	}
	return (manage_str(&fd_content, line));
}

/*
#include <stdio.h>
int main(int ac, char **av)
{
	(void)ac;

	int fd = open(av[1], O_RDONLY);
	char *line = NULL;

	printf("%d %s\n", get_next_line(fd, &line), line);
	printf("%d %s\n", get_next_line(fd, &line), line);
	printf("%d %s\n", get_next_line(fd, &line), line);
	printf("%d %s\n", get_next_line(fd, &line), line);
	return 0;
}
*/
