#include "get_next_line.h"

void	ft_putstr(char *str)
{
	if (!str)
		write(1,"no\n", 3);
	else
		write(1, str, ft_strlen(str));
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
