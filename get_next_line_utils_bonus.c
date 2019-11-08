/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/07 14:42:17 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_del(t_gnl **ptr)
{
	t_gnl	*tmp;
	t_gnl	*prev;
	t_gnl	*after;

	prev = NULL;
	if (*ptr == (*ptr)->first)
	{
		tmp = (*ptr)->next;
		free((*ptr)->content);
		(*ptr)->next = NULL;
		free(*ptr);
		*ptr = tmp;
	}
	else
	{
		tmp = (*ptr)->first;
		while (tmp)
		{
			if (tmp == *ptr)
			{
				if (prev)
					prev->next = (*ptr)->next;
				after = (*ptr)->next;
				free((*ptr)->content);
				free(*ptr);
				tmp = after;
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	lens;
	unsigned int	i;

	i = 0;
	lens = ft_strlen(dest);
	while (src[i] && i < nb)
		dest[lens++] = src[i++];
	dest[lens] = '\0';
	return (dest);
}

/*char	*ft_strnew(int size)
{
	char*ptr;
	int i;

	if (!(ptr = (char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		ptr[i++] = 0;
	return (ptr);
	}*/

int		ft_strlen(char *str)
{
	int i;
	int lens;

	i = -1;
	lens = 0;
	if (str)
		while (str[++i])
			lens++;
	return (lens);
}

t_gnl	*init_fd_content(int fd, t_gnl *fd_content)
{
	t_gnl *tmp;

	tmp = NULL;
	if (!(tmp = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	tmp->fd = fd;
	tmp->content = NULL;
	if (!fd_content)
		tmp->first = tmp;
	else
		tmp->first = fd_content->first;
	tmp->next = NULL;
	return (tmp);
}

t_gnl	*get_fd(int fd, t_gnl *fd_content)
{
	if (!fd_content)
		return (init_fd_content(fd, fd_content));
	while (fd_content && fd_content->fd != fd && fd_content->next)
	{
		fd_content = fd_content->next;
	}
	if (fd_content->fd == fd)
		return (fd_content);
	else
	{
		fd_content->next = init_fd_content(fd, fd_content);
		return (fd_content->next);
	}
}
