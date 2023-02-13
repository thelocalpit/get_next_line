/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalasch <pfalasch@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:15:48 by pfalasch          #+#    #+#             */
/*   Updated: 2023/02/13 18:00:56 by pfalasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

/* In the given code, OPEN_MAX is used as an array size to define
the line array. The line array is defined as a static array 
of character pointers, and each element of the array is indexed 
by a file descriptor (fd).

When the function get_next_line is called with a file descriptor fd, 
it accesses the corresponding element in the line array using 
the expression line[fd]. The purpose of this array is to store a 
buffer of characters for each file descriptor, so that subsequent 
calls to get_next_line with the same file descriptor can access 
the same buffer and retrieve the next line of text from the file.

So, OPEN_MAX represents the maximum number of open files that can 
be processed by the function simultaneously. This value determines 
the size of the line array, and therefore the maximum number of 
file descriptors that the function can handle. */

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*string_out;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = get_line(fd, line[fd]);
	if (!line[fd])
		return (NULL);
	string_out = get_new_line(line[fd]);
	line[fd] = clean_new_line(line[fd]);
	return (string_out);
}

int main(void)
{
	int fd;
	char *line;

	fd = open("test_file.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return 1;
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	if (close(fd) == -1)
	{
		printf("Failed to close file\n");
		return 1;
	}
	
	return 0;
}
