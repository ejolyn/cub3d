/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:53:41 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:01:42 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			check_resol(t_data *img, char *str)
{
	if (*str != ' ')
		ft_error(img, "No spaces in string of description file");
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == ' ')
		str++;
	else
		ft_error(img, "Invalid resolution");
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '\0')
		return ;
	else
		ft_error(img, "Invalid resolution");
}

int				check_argv(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '.' && argv[i] != '\0')
		i++;
	if (argv[i] == '\0')
		return (1);
	i++;
	if (argv[i] == 'c' && argv[i + 1] == 'u' &&
		argv[i + 2] == 'b' && argv[i + 3] == '\0')
	{
		if ((i = open(argv, O_DIRECTORY)) > 0)
			return (1);
		return (0);
	}
	return (1);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_get_color_sprite(t_sprite *img, int x, int y)
{
	unsigned int	color;

	color = *(int *)(img->addr + ((x + (y * img->texturewidth))
		* (img->bits_per_pixel / 8)));
	return (color);
}

unsigned int	my_mlx_get_color(t_images *img, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(img->addr + ((x + (y * img->texturewidth))
		* (img->bits_per_pixel / 8)));
	return (color);
}
