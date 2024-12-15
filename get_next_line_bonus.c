/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltuan-mi <ltuan-mi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:40:18 by ltuan-mi          #+#    #+#             */
/*   Updated: 2024/12/15 19:56:54 by ltuan-mi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	return (join);
}

char	*read_file(int fd, char *buffer)
{
	char	*newline;
	int		bytes_read;

	newline = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!newline)
		return (NULL);
	bytes_read = read(fd, newline, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		newline[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, newline);
		if (!buffer)
			break ;
		if (ft_strchr(newline, '\n'))
			break ;
		bytes_read = read(fd, newline, BUFFER_SIZE);
	}
	free(newline);
	if (bytes_read < 0 || (!buffer || buffer[0] == '\0'))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*my_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_buffer(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = my_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = update_buffer(buffer);
	return (line);
}
