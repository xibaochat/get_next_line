#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int          ft_strlen(char *str)
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

char *get_content_fron_file(int fd, char *str)
{
	int nb_read;
	char *s;
	char *buff;

	if (!(buff = (char *)malloc(BUFFER_SIZE + 1)))
		return (NULL);
	buff[BUFFER_SIZE] = '\0';
	nb_read = read(fd, buff, BUFFER_SIZE);
	buff[nb_read] = '\0';
	if (nb_read > 0)
	{
		s =(char *)malloc(sizeof(char) * (ft_strlen(str) + nb_read + 1));
		if (!s)
			return (NULL);
		if (str)
			s = strcat(s, str);
		s = strncat(s, buff, nb_read);
		if (no_newline_in_str(s))
			return (get_content_fron_file(fd, s));
		return (s);
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
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i] = '\0';
	s = strncpy(s, str, i);
	return (s);
}

char *remove_str(char *str)
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
	s = (char *)malloc(sizeof(char) * j);
	if (!s)
		return (NULL);
	s[--j] = '\0';
	i = ft_strlen(str);
	while (--j >= 0)
		s[j] = str[--i];
	return (s);
}

int get_next_line(int fd, char **line)
{
	static char *str = NULL;

	if (no_newline_in_str(str))
		if (!(str = get_content_fron_file(fd, str)))
			return (-1);
	*line = extract_line(str);
	str = remove_str(str);
	if (*line)
	{
		if (str[0])
			return (1);
		return (0);
	}
	return (-1);
}
