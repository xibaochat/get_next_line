/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/10 16:19:58 by xinwang          ###   ########.fr       */
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

static int			get_content_from_file(int fd, char **str)
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
	if (!(s = ft_strnew(ft_strlen(*str) + nb_read + 1)))
		return (-1);
	if (*str)
	{
		s = ft_strncat(s, *str, ft_strlen(*str));
		free(*str);
	}
	*str = ft_strncat(s, buff, nb_read);
	free(buff);
	if (no_newline_in_str(*str))
		return (get_content_from_file(fd, str));
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
		return (nigun_static(str, 0));
	if ((s1 = ft_strnew(*j)))
	{
		tmp = ft_strncat(s1, *str + *i + 1, *j - 1);
		free(*str);
		*str = tmp;
		return (1);
	}
	return (nigun_static(str, -1));
}

static int			manage_str(char **str, char **line)
{
	int res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = 0;
	if ((res = extract_line(line, str, &i, &j) != 1))
	{
		if (res == -1)
			return (nigun_static(str, -1));
		return (nigun_static(str, 0));
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static char *str = NULL;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (no_newline_in_str(str))
	{
		if (get_content_from_file(fd, &str) == -1)
			return (nigun_static(&str, -1));
		if (!str)
		{
			*line = ft_strnew(1);
			return (0);
		}
	}
	return (manage_str(&str, line));
}
