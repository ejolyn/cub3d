/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:22:29 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 11:58:32 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
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
	data->move_w = 0;
	data->move_a = 0;
	data->move_s = 0;
	data->move_d = 0;
	data->rotate = 0;
	data->map = NULL;
}

void	init_plr2(t_data *img)
{
	if (img->player.orientation == 'W')
	{
		img->player.directy = -1;
		img->player.planex = -0.66;
	}
	else if (img->player.orientation == 'E')
	{
		img->player.directy = 1;
		img->player.planex = 0.66;
	}
	img->player.directx = 0;
	img->player.planey = 0;
}

void	init_plr(t_data *img)
{
	if (img->player.orientation == 'N' || img->player.orientation == 'S')
	{
		if (img->player.orientation == 'N')
		{
			img->player.directx = -1;
			img->player.planey = 0.66;
		}
		else if (img->player.orientation == 'S')
		{
			img->player.directx = 1;
			img->player.planey = -0.66;
		}
		img->player.directy = 0;
		img->player.planex = 0;
	}
	else
	{
		init_plr2(img);
	}
}

void	ft_init_images_continue(t_data *img)
{
	free(img->textures.sprite);
	img->images[0].addr = mlx_get_data_addr(img->images[0].img,
		&(img->images[0].bits_per_pixel), &(img->images[0].line_length),
			&(img->images[0].endian));
	img->images[1].addr = mlx_get_data_addr(img->images[1].img,
		&(img->images[1].bits_per_pixel), &(img->images[1].line_length),
			&(img->images[1].endian));
	img->images[2].addr = mlx_get_data_addr(img->images[2].img,
		&img->images[2].bits_per_pixel,
			&img->images[2].line_length, &img->images[2].endian);
	img->images[3].addr = mlx_get_data_addr(img->images[3].img,
		&img->images[3].bits_per_pixel,
			&img->images[3].line_length, &img->images[3].endian);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img,
		&img->sprite.bits_per_pixel,
			&img->sprite.line_length, &img->sprite.endian);
}

void	ft_init_images(t_data *img)
{
	if (!(img->images[0].img = mlx_xpm_file_to_image(img->mlx,
		img->textures.north, &img->images[0].texturewidth,
			&img->images[0].textureheight)))
		ft_error(img, "Some troubles with xpm file");
	free(img->textures.north);
	if (!(img->images[1].img = mlx_xpm_file_to_image(img->mlx,
		img->textures.south, &img->images[1].texturewidth,
			&img->images[1].textureheight)))
		ft_error(img, "Some troubles with xpm file");
	free(img->textures.south);
	if (!(img->images[2].img = mlx_xpm_file_to_image(img->mlx,
		img->textures.west, &img->images[2].texturewidth,
			&img->images[2].textureheight)))
		ft_error(img, "Some troubles with xpm file");
	free(img->textures.west);
	if (!(img->images[3].img = mlx_xpm_file_to_image(img->mlx,
		img->textures.east, &img->images[3].texturewidth,
			&img->images[3].textureheight)))
		ft_error(img, "Some troubles with xpm file");
	free(img->textures.east);
	if (!(img->sprite.img = mlx_xpm_file_to_image(img->mlx,
		img->textures.sprite, &img->sprite.texturewidth,
			&img->sprite.textureheight)))
		ft_error(img, "Some troubles with xpm file");
	ft_init_images_continue(img);
}
