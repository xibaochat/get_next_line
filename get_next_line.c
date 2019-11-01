#include "get_next_line.h"

static int no_newline_in_str(char *str)
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

static int get_content_fron_file(int fd, t_gnl *fd_content)
{
	int nb_read;
	char *s;
	char *buff;

	buff = ft_strnew(BUFFER_SIZE + 1);
	if ((nb_read = read(fd, buff, BUFFER_SIZE)) < 0)
		return (0);
	if (nb_read)
	{
		buff[nb_read] = '\0';
		if (!(s = ft_strnew(ft_strlen(fd_content->content) +	\
							nb_read + 1)))
			return (0);
		if (fd_content->content)
		{
			s = ft_strcat(s, fd_content->content);
			free(fd_content->content);
		}
		s = ft_strcat(s, buff);
		free(buff);
		fd_content->content = s;
		if (no_newline_in_str(fd_content->content))
			return (get_content_fron_file(fd, fd_content));
		return (1);
	}
	free(buff);
	return (0);
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
		return (ft_strncpy(s, str, i));
	return (NULL);
}

static int remove_str(t_gnl *fd_content)
{
	int i;
	int j;
	char *s;

	i = 0;
	j = 0;
	if (!(fd_content->content))
		return (0);
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
	s = ft_strnew(j);
	if (s)
	{
		s = ft_strcat(s, fd_content->content + i + 1);
		if (fd_content->content)
			free(fd_content->content);
		fd_content->content = s;
		return (1);
	}
	return (0);
}

static t_gnl	*init_fd_content(int fd, t_gnl *fd_content)
{
	static t_gnl	*tmp;

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

int get_next_line(int fd, char **line)
{
	static t_gnl *fd_content = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	// CHAINLIST INIT
	while (fd_content && fd_content->fd != fd && fd_content->next)
		fd_content = fd_content->next;
	if (!fd_content)
		fd_content = init_fd_content(fd, NULL);
	else if (fd_content && !(fd_content->next) && fd_content->fd != fd)
	{
		fd_content->next = init_fd_content(fd, fd_content);
		fd_content = fd_content->next;
	}
	if (fd_content->reach_eof)
		return (-1);
\
	// READ
	if (no_newline_in_str(fd_content->content))
		if (!(get_content_fron_file(fd, fd_content)))
			return (-1);

	// IN CASE OF EMPTY FILE
	if (!fd_content->content)
	{
		*line = NULL;
		return (0);
	}

	// EXTRACT
	*line = extract_line(fd_content->content);

	// REMOVE
	remove_str(fd_content);
	// RETURN VALUE
	if (fd_content->reach_eof)
	{
		fd_content = fd_content->first;
		return (0);
	}
	fd_content = fd_content->first;
	return (1);
}
