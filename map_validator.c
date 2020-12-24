/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:41:42 by ejolyn            #+#    #+#             */
/*   Updated: 2020/12/24 15:22:03 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_textures(t_textures *parse_text, t_data *img)
{
	parse_text->north = NULL;
	parse_text->south = NULL;
	parse_text->east = NULL;
	parse_text->west = NULL;
	parse_text->sprite = NULL;
	img->resolution_h = 0;
	img->resolution_w = 0;
	parse_text->color_ceiling = 0;
	parse_text->color_floor = 0;
}

int check_textures(t_textures *parse_text, t_data *img)
{
	if (parse_text->north == NULL)
		return (1);
	if (parse_text->south == NULL)
		return (1);
	if (parse_text->east == NULL)
		return (1);
	if (parse_text->west == NULL)
		return (1);
	if (parse_text->sprite == NULL)
		return (1);
	if (img->resolution_h == 0 || img->resolution_w == 0)
		return (1);
	if (parse_text->color_ceiling == 0)
		return (1);
	if (parse_text->color_floor == 0)
		return (1);
	return (0);
}

void ft_parse_resolution(t_data *img, char* str)
{
	str++;
	if (img->resolution_h != 0 || img->resolution_w != 0)
		ft_error(img, "Double resolution in map file");
	if (str[0] != ' ')
		ft_error(img, "No spaces in string of description file");
	img->resolution_w = ft_atoi(str);
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str >= '0' && *str <= '9')
		img->resolution_h = ft_atoi(str);
	else
		ft_error(img, "Wrong resolution");
}

void ft_parse_colors(t_data *img, t_textures *parse_text, char* str)
{
	int r;
	int g;
	int b;
	int flag;

	flag = (*str == 'F') ? 1 : 2;
	str += 1;
	if ((flag == 1 && parse_text->color_floor != 0) || (flag == 2 && parse_text->color_ceiling != 0))
		ft_error(img, "Double string with color information");
	while (*str == ' ')
		str++;
	r = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == ',')
		str++;
	g = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == ',')
		str++;
	b = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_error(img, "Wrong color information");
	if (flag == 1)
		parse_text->color_floor = ((1 << 24) + (r << 16) + (g << 8) + b);
	else if (flag == 2)
		parse_text->color_ceiling = ((1 << 24) + (r << 16) + (g << 8) + b);
}

void ft_parse_textures(t_data *img, t_list **head)
{
	t_textures *parse_text = (t_textures*)malloc(sizeof(t_textures*));
	t_list	*tmp = *head;
	char	*tmp2;

	init_textures(parse_text, img);
	while (check_textures(parse_text, img) && tmp)
	{
		tmp2 = tmp->content;
		if (tmp2[0] == 'R')
			ft_parse_resolution(img, tmp2);
		if (tmp2[0] == 'F' || tmp2[0] == 'C')
			ft_parse_colors(img, parse_text, tmp2);
		tmp = tmp->next;
	}
}

char	**parser(int fd, t_data *img)
{
	t_list	*head = NULL;
	char	*line;
	char	**map;

	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	// ft_parse_textures(img, &head);
	map = make_map(&head, ft_lstsize(head)); // очистить память в спискe после создания карты 
	// if (!validate_map(img, map))
	// {
	// 	ft_error(img, "Map error");
	// 	return (NULL);
	// }
	img->error = 0;
	return (map);
}

// int validate_map(t_data *img, char **map)
// {
// 	f
// }

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

