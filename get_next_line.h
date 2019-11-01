#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_gnl
{
	int fd;
	char *content;
	int reach_eof;
	struct s_gnl *first;
	struct s_gnl *next;
}				t_gnl;

int            ft_strlen(char *str);
char*           ft_strcat(char *dest, char *src);
char *ft_strncpy(char *dest, char *src, int n);
char *ft_strnew(int size);
int no_newline_in_str(char *str);

#endif
