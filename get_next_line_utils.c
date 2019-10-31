#include "get_next_line.h"

void	ft_putstr(char *str)
{
	if (!str)
		write(1,"no\n", 3);
	else
		write(1, str, ft_strlen(str));
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

char	*ft_strncat(char *dest, char *src, int n)
{
	 unsigned int lens;
	 unsigned int i;

	 i = 0;
	 lens = ft_strlen(dest);
	 while (src[i] && i < n)
		 dest[lens++] = src[i++];
	 dest[lens] = '\0';
	 return (dest);
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
