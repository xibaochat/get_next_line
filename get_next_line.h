/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:44 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/10 16:04:06 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int				ft_strlen(char *str);
char			*ft_strnew(int size);
int				get_next_line(int fd, char **line);
char			*ft_strncat(char *dest, char *src, unsigned int nb);
int				nigun_static(char   **str, int return_value);

#endif
