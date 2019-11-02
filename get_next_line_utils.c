#include "get_next_line.h"

static t_gnl    *init_fd_content(int fd, t_gnl *fd_content)
{
	t_gnl    *tmp;

	if (!(tmp = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	if (!fd_content)
		tmp->first = tmp;
	else
		tmp->first = fd_content->first;
	tmp->fd = fd;
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->reach_eof = 0;
	return (tmp);
}

t_gnl *get_fd_content(int fd, t_gnl *fd_content)
{
	while (fd_content && fd_content->fd != fd && fd_content->next)
		fd_content = fd_content->next;
	if (!fd_content)
		fd_content = init_fd_content(fd, NULL);
	else if (fd_content && !(fd_content->next) && fd_content->fd != fd)
	{
		fd_content->next = init_fd_content(fd, fd_content);
		fd_content = fd_content->next;
	}
	return (fd_content);
}

int no_newline_in_str(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char *ft_strnew(int size)
{
	char *ptr;
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
	int  i;
	int  lens;

	i = -1;
	lens = 0;
	if (str)
		while (str[++i])
			lens++;
	return (lens);
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;
	while  (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = ft_strlen(dest);
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}
