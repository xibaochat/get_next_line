#include "get_next_line.h"

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
		s = ft_strcat(s, fd_content->content);
		free(fd_content->content);
	}
	fd_content->content = ft_strcat(s, buff);
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
		s = ft_strcat(s, fd_content->content + i + 1);
		if (fd_content->content)
			free(fd_content->content);
		fd_content->content = s;
		return (1);
	}
	return (0);
}


int get_next_line(int fd, char **line)
{
	static t_gnl *fd_content = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	fd_content = get_fd_content(fd, fd_content);
	if (fd_content->reach_eof)
		return (-1);
	// READ
	if (no_newline_in_str(fd_content->content))
		if ((get_content_fron_file(fd, fd_content)) == -1)
			return (-1);
	// IN CASE OF EMPTY FILE
	if (!fd_content->content)
	{
		*line = ft_strnew(1);
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
