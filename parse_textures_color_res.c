/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_color_res.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 08:59:54 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 13:05:34 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_textures(t_data *img, char **texture, char *line)
{
	int i;
	int j;

	i = 2;
	j = 0;
	if ((*texture) != NULL)
		ft_error(img, "Double textures");
	while (line[i] == ' ')
		i++;
	if (line[i] != '.' && line[i + 1] != '/')
		ft_error(img, "Wrong path to textures");
	if (!(*texture = (char *)malloc(sizeof(char) * ft_strlen(line) - i + 1)))
		ft_error(img, "Trouble with malloc");
	while (line[i] != '\0')
		(*texture)[j++] = line[i++];
	(*texture)[j] = '\0';
	if ((j = open(*texture, O_RDONLY)) < 0)
		ft_error(img, "Wrong path to textures");
}

void	ft_parse_resolution(t_data *img, char *str)
{
	str++;
	if (img->textures.resolution_h != 0 || img->textures.resolution_w != 0)
		ft_error(img, "Double resolution in map file");
	check_resol(img, str);
	img->textures.resolution_w = ft_atoi(str);
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str >= '0' && *str <= '9')
		img->textures.resolution_h = ft_atoi(str);
	else
		ft_error(img, "Wrong resolution");
	mlx_get_screen_size(img->mlx, &img->screen_w, &img->screen_h);
	if (img->textures.resolution_w > img->screen_w ||
		img->textures.resolution_w < 0 || img->textures.resolution_h >
			img->screen_h || img->textures.resolution_h < 0)
	{
		img->textures.resolution_w = img->screen_w;
		img->textures.resolution_h = img->screen_h;
	}
}

void	check_color(t_data *img, char *str)
{
	if (*str != ' ')
		ft_error(img, "No spaces in string of description file");
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str++ != ',')
		ft_error(img, "Invalid color information");
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str++ != ',')
		ft_error(img, "Invalid color information");
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
		ft_error(img, "Invalid color information");
}

void	ft_parse_color_floor(t_data *img, char *str)
{
	int r;
	int g;
	int b;

	str += 1;
	check_color(img, str);
	if (img->textures.color_floor > 0)
		ft_error(img, "Double string with color information");
	while (*str == ' ')
		str++;
	r = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ',' || *str == ' ')
		str++;
	g = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ',' || *str == ' ')
		str++;
	b = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_error(img, "Wrong color information");
	img->textures.color_floor = ((1 << 24) + (r << 16) + (g << 8) + b);
}

void	ft_parse_color_ceiling(t_data *img, char *str)
{
	int r;
	int g;
	int b;

	str += 1;
	check_color(img, str);
	if (img->textures.color_ceiling > 0)
		ft_error(img, "Double string with color information");
	while (*str == ' ')
		str++;
	r = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ',' || *str == ' ')
		str++;
	g = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ',' || *str == ' ')
		str++;
	b = (*str >= '0' && *str <= '9') ? ft_atoi(str) : -1;
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_error(img, "Wrong color information");
	img->textures.color_ceiling = ((1 << 24) + (r << 16) + (g << 8) + b);
}
