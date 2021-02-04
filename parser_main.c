/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:41:42 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/02 16:53:31 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_textures(t_textures *parse_text)
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

// int check_textures(t_textures *parse_text, t_data *img)
// {
// 	if (parse_text->north == NULL)
// 		return (1);
// 	if (parse_text->south == NULL)
// 		return (1);
// 	if (parse_text->east == NULL)
// 		return (1);
// 	if (parse_text->west == NULL)
// 		return (1);
// 	if (parse_text->sprite == NULL)
// 		return (1);
// 	if (img->resolution_h == 0 || img->resolution_w == 0)
// 		return (1);
// 	if (parse_text->color_ceiling == -1)
// 		return (1);
// 	if (parse_text->color_floor == -1)
// 		return (1);
// 	return (0);
// }



void ft_parse_all(t_data *img, char *line)
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
	else
		img->error = 1;
}

char	**parser(int fd, t_data *img)
{
	t_list	*head = NULL;
	char	*line;
	char	**map;
	t_textures *parse_text = (t_textures*)malloc(sizeof(t_textures*));
	int		flag = 1;

	img->textures = *parse_text;
	init_textures(&img->textures);
	while ((flag = get_next_line(fd, &line)) && line[0] != '1' && line[0] != '0' && line[0] != ' ')
	{
		if (line[0] == '\0')
			continue ;
		ft_parse_all(img, line);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	map = make_map(&head, ft_lstsize(head));
	return (map);
}

void	ft_error(t_data *img, char *error)
{
	write(1, "Error\n", 6);
	if (img->error == GAME_ERROR)
	{
		write(1, error, ft_strlen(error));
		mlx_destroy_window(img->mlx, img->win);
	}
	if (img->error == MAP_ERROR || img->error == READ_ERROR)
		write(1, error, ft_strlen(error));
	else
		write(1, error, ft_strlen(error));
	exit(0);
}

