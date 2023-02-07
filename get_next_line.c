/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalasch <pfalasch@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:45:43 by pfalasch          #+#    #+#             */
/*   Updated: 2023/02/07 18:57:18 by pfalasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd, char *line)
{
	char	*buf;
	size_t	i;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	i = 1;
	while (!(ft_strchr(line, '\n')) && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		line = ft_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

char	*get_new_line(char *line)
{
	size_t	len;
	char	*s2;

	len = 0;
	while (line[len] != '\n' || line[len])
		len++;
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (0);
	ft_memcpy(s2, line, (len + 1));
	return (s2);
}

char	*clean_new_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n' ||)
		i++;
	return (line + i + 1);
}

int	*get_next_line(int fd)
{
	static char	*line;
	char		*string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(line);
	string = get_new_line(line);
	line = clean_new_line(line);
	return (string);
}