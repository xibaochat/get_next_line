/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/09 02:48:25 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strnew(int size)
{
	char*ptr;
	int i;

	if (!(ptr = (char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		ptr[i++] = 0;
	return (ptr);
}

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

int		ft_lstdel(t_gnl **begin_list, t_gnl *this)
{
	t_gnl *tmp;

	free(this->content);
	if (*begin_list == this)
		*begin_list = this->next;
	else
	{
		tmp = *begin_list;
		while (tmp && tmp->next && (tmp->next != this))
			tmp = tmp->next;
		tmp->next = this->next;
	}
	free(this);
	return (-1);
}

t_gnl	*get_fd(int fd, t_gnl **begin_list)
{
	t_gnl	*current;
	t_gnl	*tmp;

	current = *begin_list;
	while (current && current->fd != fd && current->next)
		current = current->next;
	if (current && current->fd == fd)
		return (current);
	if (!(tmp = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	tmp->fd = fd;
	tmp->content = ft_strnew(1);
	tmp->next = NULL;
	if (current)
		current->next = tmp;
	else
		*begin_list = tmp;
	return (tmp);
}
