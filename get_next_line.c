/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalasch <pfalasch@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:45:43 by pfalasch          #+#    #+#             */
/*   Updated: 2023/02/10 16:32:07 by pfalasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd, char *line)
{
	char	*buf;
	int		i;

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
	int		i;
	char	*next_str;

	i = 0;
	while (line[i] != '\n' || line[i])
		i++;
	next_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!next_str)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		next_str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		next_str[i++] = '\n';
	}
	next_str[i] = 0;
	return (next_str);
}

char	*clean_new_line(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	line = &line[i];
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!tmp)
		return (NULL);
	while (line[i])
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	free(line);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*string_out;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(fd, line);
	if (!line)
		return (NULL);
	string_out = get_new_line(line);
	line = clean_new_line(line);
	return (string_out);
}
