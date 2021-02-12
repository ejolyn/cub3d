/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:51:51 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 13:50:48 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../cub3d.h"

int		ft_save_line(char **arr, char **line, int fd)
{
	char	*tmp;
	char	*flag_n;

	if (!(flag_n = ft_strchr(arr[fd], '\n')))
	{
		*line = ft_strdup(arr[fd]);
		free(arr[fd]);
		arr[fd] = NULL;
		return (0);
	}
	else
	{
		*flag_n++ = '\0';
		*line = ft_strdup(arr[fd]);
		tmp = ft_strdup(flag_n);
		free(arr[fd]);
		arr[fd] = tmp;
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*arr[256];
	char			buf[BUFFER_SIZE + 1];
	int				reading_bytes;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((reading_bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[reading_bytes] = '\0';
		if (arr[fd] == NULL)
			arr[fd] = ft_strdup("");
		tmp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = tmp;
		if (ft_strchr(arr[fd], '\n'))
			break ;
	}
	if (reading_bytes == 0 && (!arr[fd] || (*arr[fd] == '\0' && *buf == '\n')))
	{
		*line = ft_strdup("");
		return (0);
	}
	return ((reading_bytes < 0) ? -1 : ft_save_line(arr, line, fd));
}
