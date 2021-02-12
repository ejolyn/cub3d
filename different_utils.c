/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:04:48 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:27:09 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_floor_ceiling(t_data *img, int x)
{
	int		i;

	i = 0;
	while (i < img->line_start)
	{
		my_mlx_pixel_put(img, x, i, img->textures.color_ceiling);
		i++;
	}
	i = img->line_end;
	while (i < img->textures.resolution_h)
	{
		my_mlx_pixel_put(img, x, i, img->textures.color_floor);
		i++;
	}
}

void	calculate_sidedist(t_data *img)
{
	if (img->player.raydirectx < 0)
	{
		img->player.stepx = -1;
		img->player.sidedistx = (img->player.x - img->mapx) *
			img->player.deltadistx;
	}
	else
	{
		img->player.stepx = 1;
		img->player.sidedistx = (1.0 + img->mapx - img->player.x) *
			img->player.deltadistx;
	}
	if (img->player.raydirecty < 0)
	{
		img->player.stepy = -1;
		img->player.sidedisty = (img->player.y - img->mapy) *
			img->player.deltadisty;
	}
	else
	{
		img->player.stepy = 1;
		img->player.sidedisty = (1.0 + img->mapy - img->player.y) *
			img->player.deltadisty;
	}
}

int		ft_close_programm(t_data *img)
{
	check_free(img);
	exit(0);
	return (0);
}

int		full_validator(t_data *img, int x, int y)
{
	int j;
	int i;
	int res;

	i = 0;
	j = 0;
	res = validator_map(img, x, y);
	while (img->map[i] != NULL)
	{
		while (img->map[i][j] != '\0')
		{
			if (img->map[i][j] == '0' && res != 0)
				res = validator_map(img, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	return (res);
}
