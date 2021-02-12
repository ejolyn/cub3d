/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:23:11 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:01:33 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bubble_sort_sprites(t_data *img)
{
	t_individual	swap;
	int				i;
	int				j;

	i = 0;
	j = 1;
	while (j <= img->sprite.numofsprites - 1)
	{
		while (i <= img->sprite.numofsprites - 1 - j)
		{
			if (img->spr_array[i].spritedistance <
				img->spr_array[i + 1].spritedistance)
			{
				swap = img->spr_array[i];
				img->spr_array[i] = img->spr_array[i + 1];
				img->spr_array[i + 1] = swap;
			}
			i++;
		}
		j++;
	}
}

void	draw_stripe_helper(t_data *img)
{
	int				d;
	unsigned int	color;

	img->sprite.texx = (int)(256 * (img->sprite.drawstartx -
		(img->sprite.sprscreenx - img->sprite.sprwidth / 2)) *
			img->sprite.texturewidth / img->sprite.sprwidth) / 256;
	if (img->sprite.transformy > 0 && img->sprite.drawstartx > 0 &&
		img->sprite.drawstartx < img->textures.resolution_w &&
			img->sprite.transformy < img->spr_buffer[img->sprite.drawstartx])
	{
		img->sprite.spr_y = img->sprite.drawstarty;
		while (img->sprite.spr_y < img->sprite.drawendy)
		{
			d = img->sprite.spr_y * 256 - img->textures.resolution_h * 128 +
				img->sprite.sprheight * 128;
			img->sprite.texy = ((d * img->sprite.textureheight) /
				img->sprite.sprheight) / 256;
			color = my_mlx_get_color_sprite(&img->sprite,
				img->sprite.texx, img->sprite.texy);
			if (color != 0)
				my_mlx_pixel_put(img,
					img->sprite.drawstartx, img->sprite.spr_y, color);
			img->sprite.spr_y++;
		}
	}
}

void	draw_stripe_sprite(t_data *img)
{
	img->sprite.sprheight = abs((int)(img->textures.resolution_h /
		img->sprite.transformy));
	img->sprite.drawstarty = img->textures.resolution_h / 2 -
		img->sprite.sprheight / 2;
	img->sprite.drawstarty =
		(img->sprite.drawstarty < 0) ? 0 : img->sprite.drawstarty;
	img->sprite.drawendy = img->textures.resolution_h / 2 +
		img->sprite.sprheight / 2;
	img->sprite.drawendy = (img->sprite.drawendy >=
		img->textures.resolution_h) ? img->textures.resolution_h
			- 1 : img->sprite.drawendy;
	img->sprite.sprwidth = img->sprite.sprheight;
	img->sprite.drawstartx = img->sprite.sprscreenx - img->sprite.sprwidth / 2;
	img->sprite.drawstartx = (img->sprite.drawstartx <
		0) ? 0 : img->sprite.drawstartx;
	img->sprite.drawendx = img->sprite.sprscreenx + img->sprite.sprwidth / 2;
	img->sprite.drawendx = (img->sprite.drawendx >=
		img->textures.resolution_w) ? img->textures.resolution_w
			- 1 : img->sprite.drawendx;
	while (img->sprite.drawstartx < img->sprite.drawendx)
	{
		draw_stripe_helper(img);
		img->sprite.drawstartx++;
	}
}

void	draw_sprites_2(t_data *img)
{
	int i;

	i = -1;
	while (++i < img->sprite.numofsprites)
	{
		img->spr_array[i].spriteorder = i;
		img->spr_array[i].spritedistance = (pow((img->player.x -
			img->spr_array[i].x), 2) +
				pow((img->player.y - img->spr_array[i].y), 2));
	}
}

void	draw_sprites(t_data *img)
{
	int	i;

	i = -1;
	draw_sprites_2(img);
	ft_bubble_sort_sprites(img);
	while (++i < img->sprite.numofsprites)
	{
		img->sprite.sprx = img->spr_array[i].x - img->player.x;
		img->sprite.spry = img->spr_array[i].y - img->player.y;
		img->sprite.invdet = 1.0 / (img->player.planex * img->player.directy -
			img->player.planey * img->player.directx);
		img->sprite.transformx = img->sprite.invdet *
			(img->player.directy * img->sprite.sprx -
				img->player.directx * img->sprite.spry);
		img->sprite.transformy = img->sprite.invdet *
			(-img->player.planey * img->sprite.sprx
				+ img->player.planex * img->sprite.spry);
		img->sprite.sprscreenx = (int)((img->textures.resolution_w / 2) *
			(1 + img->sprite.transformx / img->sprite.transformy));
		draw_stripe_sprite(img);
	}
	free(img->spr_buffer);
}
