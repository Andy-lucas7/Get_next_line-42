/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:55:58 by lserrao-          #+#    #+#             */
/*   Updated: 2024/11/09 08:30:04 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(line, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free (line);
			free (buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free (buffer);
	return (line);
}

char	*new_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free (line);
	return (str);
}

char	*ft_get_next_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	str = (char *)malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_line(fd, line);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	next_line = ft_get_next_line(line);
	if (!next_line)
	{
		free (line);
		line = NULL;
		return (NULL);
	}
	line = new_line(line);
	return (next_line);
}

// int	main(void)
// {
// 	char	*ptr = NULL;
// 	int		fd = open("test.txt", O_RDWR);

// 	if (fd == -1)
// 		return (1);

// 	while ((ptr = get_next_line(fd) ) != NULL)
// 	{
// 		printf("%s", ptr);
// 		free(ptr);
// 	}
// 	close(fd);
// 	return (0);
// }
