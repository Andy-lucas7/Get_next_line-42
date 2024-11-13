/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:39:40 by lserrao-          #+#    #+#             */
/*   Updated: 2024/11/11 16:03:43 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*line[OPEN_MAX];
	char		*result_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = ft_read_line(fd, line[fd]);
	if (!line[fd])
	{
		free(line[fd]);
		return (NULL);
	}
	result_line = ft_get_next_line(line[fd]);
	if (!result_line)
	{
		free (line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	line[fd] = new_line(line[fd]);
	return (result_line);
}

// int	main(void)
// {
// 	int		i;
// 	int		fd = open("test.txt", O_RDWR);
// 	int		fd2 = open("test2.txt", O_RDWR);
// 	int		fd3 = open("test3.txt", O_RDWR);
// 	int		fd4 = open("test4.txt", O_RDWR);

// 	i = 1;
// 	if (fd == -1)
// 		return (1);
// 	while (i < 10)
// 	{
// 		printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd2));
// 		printf("%s", get_next_line(fd3));
// 		printf("%s", get_next_line(fd4));
// 		i++;
// 	}
// 	close(fd);
// 	close(fd2);
// 	close(fd3);
// 	close(fd4);
// 	return (0);
// }
