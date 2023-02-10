/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalasch <pfalasch@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:46:46 by pfalasch          #+#    #+#             */
/*   Updated: 2023/02/10 18:24:28 by pfalasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

/* char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0' && c != *s)
		s++;
	if (*s == c)
		return ((char *)s);
	return (0);
} */

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *line, char *buf)
{
	char	*new_str;
	int		i;
	int		j;

	if (!buf)
		return (NULL);
	if (!line)
	{
		line = (char *)malloc(sizeof(char) * 1);
		line[0] = '\0';
	}
	new_str = malloc((ft_strlen(line) + ft_strlen(buf) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		new_str[i] = line[i];
		i++;
	}
	while (buf[j])
		new_str[i++] = buf[j++];
	new_str[i] = '\0';
	free(line);
	return (new_str);
}
