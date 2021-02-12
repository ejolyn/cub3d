/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:41:42 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 13:43:44 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_textures *parse_text)
{
	parse_text->north = NULL;
	parse_text->south = NULL;
	parse_text->east = NULL;
	parse_text->west = NULL;
	parse_text->sprite = NULL;
	parse_text->resolution_h = 0;
	parse_text->resolution_w = 0;
	parse_text->color_ceiling = -1;
	parse_text->color_floor = -1;
}

void	ft_parse_all(t_data *img, char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		ft_parse_resolution(img, line);
	else if (line[0] == 'C')
		ft_parse_color_ceiling(img, line);
	else if (line[0] == 'F')
		ft_parse_color_floor(img, line);
	else if (line[0] == 'N' && line[1] == 'O')
		ft_parse_textures(img, &img->textures.north, line);
	else if (line[0] == 'S' && line[1] == 'O')
		ft_parse_textures(img, &img->textures.south, line);
	else if (line[0] == 'S' && line[1] == ' ')
		ft_parse_textures(img, &img->textures.sprite, line);
	else if (line[0] == 'W' && line[1] == 'E')
		ft_parse_textures(img, &img->textures.west, line);
	else if (line[0] == 'E' && line[1] == 'A')
		ft_parse_textures(img, &img->textures.east, line);
	else if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	else
		ft_error(img, "Invalid map information");
	free(line);
}

void	check_all_data(t_data *img)
{
	if (img->textures.color_ceiling == -1 || img->textures.color_floor == -1
		|| img->textures.resolution_w == 0 || img->textures.resolution_h == 0 ||
			img->textures.north == NULL || img->textures.south == NULL ||
				img->textures.west == NULL || img->textures.east == NULL)
		ft_error(img, "Some strings in map are missing");
}

char	**parser(int fd, t_data *img)
{
	t_list		*head;
	char		*line;
	char		**map;

	head = NULL;
	init_textures(&img->textures);
	while ((get_next_line(fd, &line)) &&
		line[0] != '1' && line[0] != '0' && line[0] != ' ')
		ft_parse_all(img, line);
	check_all_data(img);
	ft_lstadd_back(&head, ft_lstnew(line));
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
		if (line[0] == '\0')
			ft_error(img, "Invalid map information");
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	map = make_map(&head, ft_lstsize(head), img);
	ft_lstclear(&head, &free);
	return (map);
}

void	ft_error(t_data *img, char *error)
{
	check_free(img);
	write(1, "Error\n", 6);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	exit(0);
}
