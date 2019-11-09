/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/09 02:31:44 by xinwang          ###   ########.fr       */
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
//	if (fd == 4 && current->content)
//		printf("++%d++ %d ++%s++\n", begin_list->fd, fd, current->content);
	if (no_newline_in_str(current->content))
	{
		if (get_content_from_file(fd, current) == -1)
			return (ft_lstdel(&begin_list, current));
	}
	res = manage_str(&current, line);
//	if (fd == 4)
//		printf("==%d== %d --%s-- &&%s&&\n", begin_list->fd, res, current->content, *line);
	if (res != 1)
		ft_lstdel(&begin_list, current);
	return (res);
}

/*
#include <stdio.h>
int main(int ac, char **av)
{
	(void)ac;

	int fd = open(av[1], O_RDONLY);
	char *line = NULL;
	int res = get_next_line(fd, &line);
	printf("%d %s\n", res, line);
	return 0;
}*/

int main(int ac, char **av)
{
	(void)ac;
	int fd0 = open(av[1], O_RDONLY);
	int fd1 = open(av[2], O_RDONLY);
	int fdo0 = open("output_f0", O_WRONLY|O_CREAT, 0644);
	int fdo1 = open("output_f1", O_WRONLY|O_CREAT, 0644);
	int res0 = 1;
	int res1 = 1;
	char *line0 = NULL;
	char *line1 = NULL;
//	printf("%d | %d\n", fd0, fd1);

	while ((res0 > 0) || (res1 > 0))
	{
		if (res0)
		{
			res0 = get_next_line(fd0, &line0);
//			printf("-------------------------- END OF %s\n", av[1]);
		}
		if (res1)
		{
			res1 = get_next_line(fd1, &line1);
//			printf("-------------------------- END OF %s\n", av[2]);
		}
		if (line0)
		{
			write(fdo0, line0, ft_strlen(line0));
			if (res0)
				write(fdo0, "\n", 1);
			free(line0);
			line0 = NULL;
		}
		if (line1)
		{
			write(fdo1, line1, ft_strlen(line1));
			if (res1)
				write(fdo1, "\n", 1);
			free(line1);
			line1 = NULL;
		}
	}
	return (0);
}
