/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:29:23 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:26:54 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_wall_dist(t_data *img, short side)
{
	if (side == 0)
		img->player.perpwalldist = ((double)img->mapx - img->player.x +
			(1 - (double)img->player.stepx) / 2) / img->player.raydirectx;
	else
		img->player.perpwalldist = ((double)img->mapy - img->player.y +
			(1 - (double)img->player.stepy) / 2) / img->player.raydirecty;
	img->player.line_h = (int)(img->textures.resolution_h /
		img->player.perpwalldist);
}

void	raycast_calcul(t_data *img, short side, int x)
{
	img->spr_buffer[x] = img->player.perpwalldist;
	if (img->player.raydirectx == 0)
		img->player.deltadisty = 0;
	else
		img->player.deltadisty = (img->player.raydirecty ==
			0) ? 1 : fabs(1 / img->player.raydirecty);
	calculate_sidedist(img);
	while (img->map[img->mapx][img->mapy] != '1')
	{
		if (img->player.sidedistx < img->player.sidedisty)
		{
			img->player.sidedistx += img->player.deltadistx;
			img->mapx += img->player.stepx;
			side = 0;
		}
		else
		{
			img->player.sidedisty += img->player.deltadisty;
			img->mapy += img->player.stepy;
			side = 1;
		}
	}
	calc_wall_dist(img, side);
	ft_draw_line(img, x, side);
}

void	raycast_main(t_data *img)
{
	int		x;
	int		side;

	x = 0;
	side = 0;
	if (!(img->spr_buffer = (double *)malloc(sizeof(double)
		* img->textures.resolution_w)))
		ft_error(img, "Trouble with malloc");
	while (x++ < img->textures.resolution_w - 1)
	{
		img->player.camerax = 2 * x / (float)(img->textures.resolution_w) - 1;
		img->player.raydirectx = img->player.directx +
			img->player.planex * img->player.camerax;
		img->player.raydirecty = img->player.directy +
			img->player.planey * img->player.camerax;
		img->mapx = (int)img->player.x;
		img->mapy = (int)img->player.y;
		if (img->player.raydirecty == 0)
			img->player.deltadistx = 0;
		else
			img->player.deltadistx = (img->player.raydirectx ==
				0) ? 1 : fabs(1 / img->player.raydirectx);
		raycast_calcul(img, side, x);
	}
	draw_sprites(img);
}

void	ft_draw_line_continue(t_data *img, int x)
{
	img->step = 1.0 * img->images[img->texnum].textureheight /
		img->player.line_h;
	img->texpos = (img->line_start -
		img->textures.resolution_h / 2 + img->player.line_h / 2) * img->step;
	ft_draw_floor_ceiling(img, x);
	while (img->line_start < img->line_end)
	{
		img->images[img->texnum].texy = (int)img->texpos &
			(img->images[img->texnum].textureheight - 1);
		img->texpos += img->step;
		img->color = my_mlx_get_color(&img->images[img->texnum],
			img->images[img->texnum].texx, img->images[img->texnum].texy);
		my_mlx_pixel_put(img, x, img->line_start, img->color);
		img->line_start++;
	}
}

void	ft_draw_line(t_data *img, int x, int side)
{
	img->line_start = -img->player.line_h / 2 + img->textures.resolution_h / 2;
	img->line_start = (img->line_start < 0) ? 0 : img->line_start;
	img->line_end = img->textures.resolution_h / 2 + img->player.line_h / 2;
	img->texnum = ft_texture_side(img, side);
	img->line_end = (img->line_end >=
		img->textures.resolution_h) ? img->textures.resolution_h
			- 1 : img->line_end;
	if (side == 0)
		img->wallx = img->player.y + img->player.perpwalldist *
			img->player.raydirecty;
	else
		img->wallx = img->player.x + img->player.perpwalldist *
			img->player.raydirectx;
	img->wallx -= floor(img->wallx);
	img->images[img->texnum].texx = (int)(img->wallx *
		(double)(img->images[img->texnum].texturewidth));
	if (side == 0 && img->player.raydirectx > 0)
		img->images[img->texnum].texx =
			img->images[img->texnum].texturewidth -
				img->images[img->texnum].texx - 1;
	else if (side == 1 && img->player.raydirectx < 0)
		img->images[img->texnum].texx =
			img->images[img->texnum].texturewidth -
				img->images[img->texnum].texx - 1;
	ft_draw_line_continue(img, x);
}
