/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/09 02:40:25 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (!(buff = (char *)malloc(BUFFER_SIZE + 1)))
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

static int			manage_str(t_gnl **current, char **line)
{
	int res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = 0;
	if ((res = extract_line(line, &((*current)->content), &i, &j)) != 1)
		return (res);
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_gnl	*begin_list = NULL;
	t_gnl			*current;
	int				res;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	current = get_fd(fd, &begin_list);
	if (no_newline_in_str(current->content))
	{
		if (get_content_from_file(fd, current) == -1)
			return (ft_lstdel(&begin_list, current));
	}
	res = manage_str(&current, line);
	if (res != 1)
		ft_lstdel(&begin_list, current);
	return (res);
}
