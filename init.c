/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:22:29 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/04 10:25:23 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_data *data)
{
	data->img = NULL;
	data->addr = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->color = 0;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->error = 0;
}

void init_plr (t_data *img)
{
	img->player.directX = -1;
	img->player.directY = 0;
	img->player.planeX = 0;
	img->player.planeY = 0.66;
}

void ft_init_images(t_data *img)
{
	img->images[0].endian = 0;
	img->images[1].endian = 0;
	img->images[2].endian = 0;
	img->images[3].endian = 0;
	img->images[4].endian = 0;
	img->images[0].bits_per_pixel = 0;
	img->images[1].bits_per_pixel = 0;
	img->images[2].bits_per_pixel = 0;
	img->images[3].bits_per_pixel = 0;
	img->images[4].bits_per_pixel = 0;
	img->images[0].line_length = 0;
	img->images[1].line_length = 0;
	img->images[2].line_length = 0;
	img->images[3].line_length = 0;
	img->images[4].line_length = 0;
	img->images[0].img = mlx_xpm_file_to_image(img->mlx, img->textures.north, &img->images[0].textureWidth, &img->images[0].textureHeight);
	img->images[1].img = mlx_xpm_file_to_image(img->mlx, img->textures.south, &img->images[1].textureWidth, &img->images[1].textureHeight);
	img->images[2].img = mlx_xpm_file_to_image(img->mlx, img->textures.west, &img->images[2].textureWidth, &img->images[2].textureHeight);
	img->images[3].img = mlx_xpm_file_to_image(img->mlx, img->textures.east, &img->images[3].textureWidth, &img->images[3].textureHeight);
	img->images[4].img = mlx_xpm_file_to_image(img->mlx, img->textures.sprite, &img->images[4].textureWidth, &img->images[4].textureHeight);
	img->images[0].addr = (int *)mlx_get_data_addr(img->images[0].img, &(img->images[0].bits_per_pixel), &(img->images[0].line_length), &(img->images[0].endian));
	img->images[1].addr = (int *)mlx_get_data_addr(img->images[1].img, &(img->images[1].bits_per_pixel), &(img->images[1].line_length), &(img->images[1].endian));
	img->images[2].addr = (int *)mlx_get_data_addr(img->images[2].img, &img->images[2].bits_per_pixel, &img->images[2].line_length, &img->images[2].endian);
	img->images[3].addr = (int *)mlx_get_data_addr(img->images[3].img, &img->images[3].bits_per_pixel, &img->images[3].line_length, &img->images[3].endian);
	img->images[4].addr = (int *)mlx_get_data_addr(img->images[4].img, &img->images[4].bits_per_pixel, &img->images[4].line_length, &img->images[4].endian);
}

int ft_texture_side(t_data *img, short side)
{
	int texNum;

	if (img->player.raydirectX < 0 && side == 0)
		texNum = 0;
	if (img->player.raydirectX >= 0 && side == 0)
		texNum = 1;
	if (img->player.raydirectY < 0 && side == 1)
		texNum = 2;
	if (img->player.raydirectY >= 0 && side == 1)
		texNum = 3;
	return texNum;
}