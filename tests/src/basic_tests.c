#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int get_next_line(int fd, char **line);

int main(int ac, char **av)
{
	(void)ac;
	char *str = NULL;
	int fd = open(av[1], O_RDONLY);
	char *line;
	int res;

	line = NULL;
	while (get_next_line(fd, &line) >= 0)
		printf("%s\n", line);
	return (0);

}
