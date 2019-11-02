#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int get_next_line(int fd, char **line);

int main(int ac, char **av)
{
	(void)ac;
	char *str = NULL;
	int fd = open(av[1], O_RDONLY);
	char *line = NULL;
	int res;

	while ((res = get_next_line(fd, &line))>= 0)
	{
		//	printf("%d\n", res);
		write(1, line, strlen(line));
		if (res)
			write(1, "\n", 1);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (0);

}
