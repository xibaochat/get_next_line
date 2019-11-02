/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/02 22:17:20 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char*   ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int lens;
	unsigned int i;

	i = 0;
	lens = ft_strlen(dest);
	while (src[i] && i < nb)
		dest[lens++] = src[i++];
	dest[lens] = '\0';
	return (dest);
}

static int get_content_fron_file(int fd, t_gnl *fd_content)
{
	int nb_read;
	char *s;
	char *buff;

	buff = ft_strnew(BUFFER_SIZE + 1);
	if ((nb_read = read(fd, buff, BUFFER_SIZE)) <= 0)
	{
		free(buff);
		return (nb_read);
	}
	buff[nb_read] = '\0';
	if (!(s = ft_strnew(ft_strlen(fd_content->content) + nb_read + 1)))
		return (0);
	if (fd_content->content)
	{
		s = ft_strncat(s, fd_content->content, ft_strlen(fd_content->content));
		free(fd_content->content);
	}
	fd_content->content = ft_strncat(s, buff, nb_read);
	free(buff);
	if (no_newline_in_str(fd_content->content))
		return (get_content_fron_file(fd, fd_content));
	return (1);
}

char *extract_line(char *str)
{
	char *s;
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	s = ft_strnew(i + 1);
	if(s)
		return (ft_strncat(s, str, i));
	return (NULL);
}

static int remove_str(t_gnl *fd_content)
{
	int i;
	int j;
	char *s;

	i = 0;
	j = 0;
	while (fd_content->content[i] && fd_content->content[i] != '\n')
		i++;
	if (!(fd_content->content[i]))
	{
		fd_content->reach_eof = 1;
		if (fd_content->content)
			free(fd_content->content);
		return (1);
	}
	j = ft_strlen(fd_content->content) - i;
	if ((s = ft_strnew(j)))
	{
		s = ft_strncat(s, fd_content->content + i + 1, ft_strlen(fd_content->content) + i + 1);
		if (fd_content->content)
			free(fd_content->content);
		fd_content->content = s;
		return (1);
	}
	return (0);
}


int	get_next_line(int fd, char **line)
{
	static t_gnl *fd_content = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	fd_content = get_fd_content(fd, fd_content);
	if (fd_content->reach_eof)
		return (0);
	if (no_newline_in_str(fd_content->content))
		if ((get_content_fron_file(fd, fd_content)) == -1)
			return (-1);
	if (!fd_content->content)
	{
		*line = ft_strnew(1);
		return (0);
	}
	*line = extract_line(fd_content->content);
	remove_str(fd_content);
	if (fd_content->reach_eof)
	{
		fd_content = fd_content->first;
		return (0);
	}
	fd_content = fd_content->first;
	return (1);
}
