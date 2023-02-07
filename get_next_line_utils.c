/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalasch <pfalasch@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:46:46 by pfalasch          #+#    #+#             */
/*   Updated: 2023/02/07 12:11:48 by pfalasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
char *ft_strchr(const char *s, int c)
{
	while (*s != '\0' && c != *s)
		s++;
	if (*s == c)
		return ((char *)s);
	return (0);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *new_str;
	int i;
	int j;

	if (!s1 || !s2)
		return (NULL);
	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_line(int fd, char *line)
{
	char	*buf;
	size_t 	i;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1);
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
		line = ft_strjoin(line, buf);
		free(buf);
	}
	free(buf);
	return (line);
}
	