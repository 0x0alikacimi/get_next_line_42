/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:40:33 by abkacimi          #+#    #+#             */
/*   Updated: 2023/12/17 19:51:36 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*the_next_line(char *buff)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	if (buff[i] == '\0')
		return (free(buff), NULL);
	line = malloc(sizeof(char) * (ft_strlen(buff) - i + 1));
	if (!line)
		return (free(buff), NULL);
	j = 0;
	while (buff[i])
		line[j++] = buff[i++];
	line[j] = '\0';
	return (free(buff), line);
}

char	*the_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*fd_read(int fd, char *result)
{
	char	*buffer;
	int		num_bytes;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(result), NULL);
	num_bytes = 1;
	while (num_bytes > 0)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
			return (free(buffer), free(result), NULL);
		buffer[num_bytes] = '\0';
		result = ft_strjoin(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), result);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = fd_read(fd, buff);
	if (!buff)
		return (NULL);
	line = the_line(buff);
	buff = the_next_line(buff);
	if (!line)
	{
		free(buff);
		buff = NULL;
	}
	return (line);
}

// #include <libc.h>
// int main()
// {
// 	int fd = open("text.txt", O_CREAT | O_RDWR, 0777);
// 	write (fd, "kacimi\nHello\ngood", 17);
// 	fd = open("text.txt", O_RDWR);
// 	char *s = get_next_line(fd);
// 	printf("%s", s);
// 	// s = get_next_line(fd);
// 	// printf("%s", s);
// 	// s = get_next_line(fd);
// 	// printf("%s", s);
// 	// s = get_next_line(fd);
// 	// printf("%s", s);
// }