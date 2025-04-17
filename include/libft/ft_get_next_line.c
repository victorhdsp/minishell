/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vide-sou <vide-sou@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:32:47 by vide-sou          #+#    #+#             */
/*   Updated: 2025/04/01 11:37:36 by vide-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	read_and_join(int fd, char **buffer)
{
	size_t	readed;
	char	*tmp;
	char	*result;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	ft_memset(tmp, 0, BUFFER_SIZE + 1);
	readed = read(fd, tmp, BUFFER_SIZE);
	if (!tmp[0])
		readed = 0;
	result = ft_strjoin(*buffer, tmp);
	if (*buffer)
		free(*buffer);
	free(tmp);
	*buffer = result;
	return (readed);
}

static char	*split_text(char **buffer, size_t index)
{
	char	*line;
	char	*remainder;
	size_t	remainder_len;

	remainder_len = ft_strlen(*buffer) - index;
	index++;
	line = malloc((index + 1) * sizeof(char));
	ft_memset(line, 0, index + 1);
	ft_memcpy(line, *buffer, index);
	remainder = malloc((remainder_len + 1) * sizeof(char));
	ft_memset(remainder, 0, remainder_len + 1);
	ft_memcpy(remainder, *buffer + index, remainder_len);
	if (*buffer)
		free(*buffer);
	*buffer = remainder;
	return (line);
}

char	*ft_get_next_line(int fd)
{
	size_t		index;
	size_t		buffer_len;
	size_t		readed;
	static char	*buffer[1024];

	index = 0;
	buffer_len = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (buffer[fd] && buffer[fd][0])
		buffer_len = ft_strlen(buffer[fd]);
	readed = buffer_len;
	while (index <= buffer_len)
	{
		if (index == buffer_len)
			readed = read_and_join(fd, &buffer[fd]);
		if (!buffer[fd])
			break ;
		if (index == buffer_len)
			buffer_len = ft_strlen(buffer[fd]);
		if (buffer[fd][index] == '\n' || readed == 0)
			return (split_text(&buffer[fd], index));
		index++;
	}
	return (NULL);
}