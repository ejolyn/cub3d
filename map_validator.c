/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:41:42 by ejolyn            #+#    #+#             */
/*   Updated: 2020/12/19 19:13:12 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parser(int fd)
{
	t_list	*head = NULL;
	char	*line;
	char	**map;

	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	map = make_map(&head, ft_lstsize(head)); // очистить память в спискe после создания карты 
	// if (!validate_map(img, map))
	// {
	// 	ft_error(img, "Map error");
	// 	return (NULL);
	// }
	return (map);
}

// int validate_map(t_data *img, char **map)
// {
// 	f
// }

void	ft_error(t_data *img, char *error)
{
	if (img->error == GAME_ERROR)
	{
		write(1, error, ft_strlen(error));
		mlx_destroy_window(img->mlx, img->win);
	}
	if (img->error == MAP_ERROR)
		write(1, error, ft_strlen(error));
	if (img->error == READ_ERROR)
		write(1, error, ft_strlen(error));
	exit(0);
}

