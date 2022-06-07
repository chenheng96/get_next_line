/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchong <cchong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:20:40 by cchong            #+#    #+#             */
/*   Updated: 2022/05/25 10:20:39 by cchong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_bzero(size_t size)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

static void	free_str(char **str)
{
	if (str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

static int	read_buffer(int fd, char *buffer, int *bytes_read)
{
	int	i;

	i = read(fd, buffer, BUFFER_SIZE);
	*bytes_read = i;
	return (i);
}

static char	*trim_line(char **str)
{
	int		i;
	char	*res;
	char	*temp;

	i = 0;
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		res = ft_substr(*str, 0, i + 1);
		temp = ft_strdup(*str + i + 1);
		free_str(str);
		if (temp[0] == '\0')
			free_str(&temp);
		else
			*str = temp;
	}
	else
	{
		res = ft_strdup(*str);
		free_str(str);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res[1024];
	char		*buffer;
	char		*temp;
	int			bytes_read;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (read_buffer(fd, buffer, &bytes_read) > 0)
	{
		buffer[bytes_read] = '\0';
		if (res[fd] == NULL)
			res[fd] = ft_bzero(1);
		temp = ft_strjoin(res[fd], buffer);
		free_str(&res[fd]);
		res[fd] = temp;
		if (ft_strchr(res[fd], '\n') != NULL)
			break ;
	}
	free_str(&buffer);
	if (bytes_read < 0 || (bytes_read == 0 && res[fd] == NULL))
		return (NULL);
	return (trim_line(&res[fd]));
}
