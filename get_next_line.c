/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalasch <pfalasch@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:45:43 by pfalasch          #+#    #+#             */
/*   Updated: 2023/02/10 19:34:26 by pfalasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "get_next_line.h"

/* questa funzione ci ricava la linea non pulita. 
ovvero ci possono essere extra caratteri */
char	*get_line(int fd, char *line)
{
	char	*buf;
	int		i;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	i = 1;
	while (i > 0 && (ft_strchr(line, '\n') == 0))
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

/* questa funzione ci ricava la linea pulita fino a \n */
char	*get_new_line(char *line)
{
	int		i;
	char	*next_str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	next_str = (char *)malloc(sizeof(char) * (i + 2));
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
		next_str[i] = '\n';
		i++;
	}
	next_str[i] = 0;
	return (next_str);
}

/* questa funzione serve per riportare in static char solo 
la parte extra presa con il buffer */
char	*clean_new_line(char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	i += 1;
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

/* int main(int argc, char *argv[])
{
	int fd;
	char *line;

	if (argc == 2)
	{
		fd = open(test.txt, O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
	}
	return (0);
} */