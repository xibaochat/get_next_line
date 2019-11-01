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

static char *get_content_fron_file(int fd, char *str)
{
	int nb_read;
	char *s;
	char *buff;

	buff = ft_strnew(BUFFER_SIZE + 1);
	nb_read = read(fd, buff, BUFFER_SIZE);
	if (nb_read < BUFFER_SIZE)
		eof = 1;

	if (!nb_read)
		return (str);
	if (nb_read > 0)
	{
		s = ft_strnew(ft_strlen(str) + nb_read + 1);
		if (s)
		{
			if (str)
				s =ft_strcat(s, str);
			s = ft_strncat(s, buff, nb_read);
			if (no_newline_in_str(s))
				get_content_fron_file(fd, s);
			//free(buff);
			//free(str);
//			printf("**%s**\n\n\n", s);
			return (s);
		}
		return (NULL);
	}
	return (NULL);
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

static char *remove_str(char *str)
{
	int i;
	int j;
	char *s;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	j = ft_strlen(str) - i;
	s = ft_strnew(j);
	if (s)
	{
		s = ft_strcat(s, str + i + 1);
		//	free(str);
		return (s);
	}
	return (NULL);
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



	// READ
	if (no_newline_in_str(fd_content->content))
	{
		if (!(fd_content->content = get_content_fron_file(fd, fd_content->content)))
			return (-1);
	}

	// EXTRACT
	*line = extract_line(fd_content->content);

	// REMOVE
	fd_content->content = remove_str(fd_content->content);

	// RETURN VALUE
	if (*line)
	{
		if ((fd_content->content)[0])
		{
			fd_content = fd_content->first;
			return (1);
		}
		fd_content = fd_content->first;
		return (0);
	}
	fd_content = fd_content->first;
	return (-1);
}
