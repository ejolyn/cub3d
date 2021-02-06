/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:49:32 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/06 18:46:10 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int make_image(t_data *img)
{
	// mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, img->textures.resolution_w, img->textures.resolution_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	processor_move_player(img);
	processor_look_player(img);
	raycast_main(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (1);
}

void calculate_sidedist(t_data *img)
{
	if (img->player.raydirectX < 0)
	{
		img->player.stepX = -1;
		img->player.sidedistX = (img->player.x - img->mapX) * img->player.deltadistX;
	}
	else
	{
		img->player.stepX = 1;
		img->player.sidedistX = (1.0 + img->mapX - img->player.x) * img->player.deltadistX;
	}
	if (img->player.raydirectY < 0)
	{
		img->player.stepY = -1;
		img->player.sidedistY = (img->player.y - img->mapY) * img->player.deltadistY;
	}
	else
	{
		img->player.stepY = 1;
		img->player.sidedistY = (1.0 + img->mapY - img->player.y) * img->player.deltadistY;
	}
}

void ft_bubble_sort_sprites(t_data *img)
{
	t_individual swap;
	int i = 0;
	int j = 1;
	
	while (j <= img->sprite.numofsprites - 1)
	{
		while (i <= img->sprite.numofsprites - 1 - j)
		{
			if (img->spr_array[i].spriteDistance < img->spr_array[i + 1].spriteDistance)
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

void draw_sprites(t_data *img, double *spr_buffer)
{
	int i = -1;

	while (++i < img->sprite.numofsprites)
	{
		img->spr_array[i].spriteOrder = i;
		img->spr_array[i].spriteDistance = (pow((img->player.x - img->spr_array[i].x), 2) + pow((img->player.y - img->spr_array[i].y), 2));
	}
	ft_bubble_sort_sprites(img);
	i = -1;
	while (++i < img->sprite.numofsprites)
	{
		img->sprite.spriteX = img->spr_array[i].x - img->player.x;
		img->sprite.spriteY = img->spr_array[i].y - img->player.y;
		img->sprite.invDet = 1.0 / (img->player.planeX * img->player.directY - img->player.planeY * img->player.directX);
		img->sprite.transformX = img->sprite.invDet * (img->player.directY * img->sprite.spriteX - img->player.directX * img->sprite.spriteY);
		img->sprite.transformY = img->sprite.invDet * (-img->player.planeY * img->sprite.spriteX + img->player.planeX * img->sprite.spriteY);
		int spriteScreenX = (int)((img->textures.resolution_w / 2) * (1 + img->sprite.transformX / img->sprite.transformY));
		int spriteHeight = abs((int)(img->textures.resolution_h / img->sprite.transformY));
		int drawStartY = img->textures.resolution_h / 2 - spriteHeight / 2;
		drawStartY = (drawStartY < 0) ? 0 : drawStartY;
		int drawEndY = img->textures.resolution_h / 2 + spriteHeight / 2;
		drawEndY = (drawEndY >= img->textures.resolution_h) ? img->textures.resolution_h - 1 : drawEndY;
		int spriteWidth = spriteHeight;
		int drawStartX = spriteScreenX - spriteWidth / 2;
		drawStartX = (drawStartX < 0) ? 0 : drawStartX;
		int drawEndX = spriteScreenX + spriteWidth / 2;
		drawEndX = (drawEndX >= img->textures.resolution_w) ? img->textures.resolution_w - 1 : drawEndX;
		int stripe = drawStartX;
		while (stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (spriteScreenX - spriteWidth / 2)) * img->sprite.textureWidth / spriteWidth) / 256;
			if (img->sprite.transformY > 0 && stripe > 0 && stripe < img->textures.resolution_w && img->sprite.transformY < spr_buffer[stripe])
			{
				int y = drawStartY;
				while (y < drawEndY)
				{
					int d = y * 256 - img->textures.resolution_h * 128 + spriteHeight * 128;
					int texY = ((d * img->sprite.textureHeight) / spriteHeight) / 256;
					unsigned int color = my_mlx_get_color_sprite(&img->sprite, texX, texY);
					if (color != 0)
						my_mlx_pixel_put(img, stripe, y, color);
					y++;
				}
			}
		stripe++;
		}
	}
}

void raycast_main(t_data *img)
{
	int x = 0;
	short side = 0;
	// int hit = 0;
	double *spr_buffer = (double *)malloc(sizeof(double) * img->textures.resolution_w);
	
	while (x++ < img->textures.resolution_w - 1)
	{
		img->player.cameraX = 2 * x / (float)(img->textures.resolution_w) - 1;
		img->player.raydirectX = img->player.directX + img->player.planeX * img->player.cameraX;
		img->player.raydirectY = img->player.directY + img->player.planeY * img->player.cameraX;
		img->mapX = (int)img->player.x;
		img->mapY = (int)img->player.y;
		img->player.deltadistX =  (img->player.raydirectX == 0) ? 1 : fabs(1 / img->player.raydirectX);
		img->player.deltadistY =  (img->player.raydirectY == 0) ? 1 : fabs(1 / img->player.raydirectY);
		calculate_sidedist(img);
		while (img->map[img->mapX][img->mapY] != '1')
		{
			if (img->player.sidedistX < img->player.sidedistY)
			{
				img->player.sidedistX += img->player.deltadistX;
				img->mapX += img->player.stepX;
				side = 0;
			}
			else
			{
				img->player.sidedistY += img->player.deltadistY;
				img->mapY += img->player.stepY;
				side = 1;
			}
			// if (img->map[img->mapX][img->mapY] != '0')
			// 	hit = 1;
		}
		if (side == 0)
			img->player.perpWallDist = (img->mapX - img->player.x + (1 - img->player.stepX) / 2) / img->player.raydirectX;
		else
			img->player.perpWallDist = (img->mapY - img->player.y + (1 - img->player.stepY) / 2) / img->player.raydirectY;
		
		img->player.line_h = (int)(img->textures.resolution_h / img->player.perpWallDist);
		img->player.line_h = (img->player.line_h >= img->textures.resolution_h) ? img->textures.resolution_h - 1 : img->player.line_h;
		ft_draw_line(img, x, side);
		spr_buffer[x] = img->player.perpWallDist;
	}
	printf("%f   %f", img->player.planeX, img->player.planeY);
	draw_sprites(img, spr_buffer);
}

void	ft_draw_line(t_data *img, int x, short side)
{
	int texNum = ft_texture_side(img, side);
	double wallX;
	int i = 0;
	int line_start = img->textures.resolution_h / 2 - img->player.line_h / 2;
	int line_end = img->textures.resolution_h / 2 + img->player.line_h / 2;

	if (side == 0)
		wallX = img->player.y + img->player.perpWallDist * img->player.raydirectY;
	else
		wallX = img->player.x + img->player.perpWallDist * img->player.raydirectX;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)(img->images[texNum].textureWidth));
	if (side == 0 && img->player.raydirectX > 0)
		texX = img->images[texNum].textureWidth - texX - 1;
	if (side == 1 && img->player.raydirectX < 0)
		texX = img->images[texNum].textureWidth - texX - 1;
	
	double step = 1.0 * img->images[texNum].textureHeight / img->player.line_h;
	line_start = (line_start < 0) ? 0 : line_start;
	line_end = (line_end >= img->textures.resolution_h) ? img->textures.resolution_h - 1 : line_end;
	double texPos = (line_start - img->textures.resolution_h / 2 + img->player.line_h / 2) * step;
	while (i < line_start)
	{
		img->color = img->textures.color_ceiling;
		my_mlx_pixel_put(img, x, i, img->color);
		i++;
	}
	while (line_start < line_end)
	{
		int texY = (int)texPos & (img->images[texNum].textureHeight - 1);
        texPos += step;
        img->color = my_mlx_get_color(&img->images[texNum], texX, texY);
		my_mlx_pixel_put(img, x, line_start, img->color);
		line_start++;
	}
	while (line_start < img->textures.resolution_h)
	{
		img->color = img->textures.color_floor;
		my_mlx_pixel_put(img, x, line_start, img->color);
		line_start++;
	}
}

void processor_look_player(t_data *img)
{
	float copydirectX = img->player.directX;
	float copyplaneX = img->player.planeX;
	if (img->rotate_l == 1)
	{
		img->player.directX = copydirectX * cos(ROTATE_SPEED) - img->player.directY * sin(ROTATE_SPEED);
		img->player.directY = copydirectX * sin(ROTATE_SPEED) + img->player.directY * cos(ROTATE_SPEED);
		img->player.planeX = copyplaneX * cos(ROTATE_SPEED) - img->player.planeY * sin(ROTATE_SPEED);
		img->player.planeY = copyplaneX * sin(ROTATE_SPEED) + img->player.planeY * cos(ROTATE_SPEED);
	}
	if (img->rotate_r == 1)
	{
		img->player.directX = copydirectX * cos(-ROTATE_SPEED) - img->player.directY * sin(-ROTATE_SPEED);
		img->player.directY = copydirectX * sin(-ROTATE_SPEED) + img->player.directY * cos(-ROTATE_SPEED);
		img->player.planeX = copyplaneX * cos(-ROTATE_SPEED) - img->player.planeY * sin(-ROTATE_SPEED);
		img->player.planeY = copyplaneX * sin(-ROTATE_SPEED) + img->player.planeY * cos(-ROTATE_SPEED);
	}
	// make_image(img);
	// mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return;
}

void processor_move_player(t_data *img)
{
	if (img->move_w == 1)
	{
		if (img->map[(int)(img->player.x + img->player.directX * MOVE_SPEED)][(int)(img->player.y)] == '0')
			img->player.x += img->player.directX * MOVE_SPEED;
		if (img->map[(int)(img->player.x)][(int)(img->player.y + img->player.directY * MOVE_SPEED)] == '0')
			img->player.y += img->player.directY * MOVE_SPEED;
	}
	if (img->move_s == 1)
	{
		if (img->map[(int)(img->player.x - img->player.directX * MOVE_SPEED)][(int)(img->player.y)] == '0')
			img->player.x -= img->player.directX * MOVE_SPEED;
		if (img->map[(int)(img->player.x)][(int)(img->player.y - img->player.directY * MOVE_SPEED)] == '0')
			img->player.y -= img->player.directY * MOVE_SPEED;
	}
	if (img->move_a == 1)
	{
		if (img->map[(int)(img->player.x - img->player.planeX * MOVE_SPEED)][(int)(img->player.y)] == '0')
			img->player.x -= img->player.planeX * MOVE_SPEED;
		if (img->map[(int)(img->player.x)][(int)(img->player.y - img->player.planeY * MOVE_SPEED)] == '0')
			img->player.y -= img->player.planeY * MOVE_SPEED;
	}
	if (img->move_d == 1)
	{
		if (img->map[(int)(img->player.x + img->player.planeX * MOVE_SPEED)][(int)(img->player.y)] == '0')
			img->player.x += img->player.planeX * MOVE_SPEED;
		if (img->map[(int)(img->player.x)][(int)(img->player.y + img->player.planeY * MOVE_SPEED)] == '0')
			img->player.y += img->player.planeY * MOVE_SPEED;
	}
	// make_image(img);
	// mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return;
}

int			ft_key_press(int keycode, t_data *img)
{
	if (keycode == ESC)
	{
    	mlx_destroy_window(img->mlx, img->win);
		exit(0);
	}
	else if (keycode == W || keycode == UP)
		img->move_w = 1;
	else if (keycode == S || keycode == DOWN)
		img->move_s = 1;
	else if (keycode == A)
		img->move_a = 1;
	else if (keycode == D)
		img->move_d = 1;
	if (keycode == LEFT)
		img->rotate_l = 1;
	if (keycode == RIGHT)
		img->rotate_r = 1;
	return 0;
}

int			ft_key_release(int keycode, t_data *img)
{
	if (keycode == W || keycode == UP)
		img->move_w = 0;
	else if (keycode == S || keycode == DOWN)
		img->move_s = 0;
	else if (keycode == A)
		img->move_a = 0;
	else if (keycode == D)
		img->move_d = 0;
	if (keycode == LEFT)
		img->rotate_l = 0;
	if (keycode == RIGHT)
		img->rotate_r = 0;
	return 0;
}

int main(int argc, char **argv)
{
	t_data	img;
	int		fd;

	if (argc != 2)
		return (0);
	init(&img);
	fd = open(argv[1], O_RDONLY);
	img.map = parser(fd, &img);
	find_player(&img);
	find_sprites(&img);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.textures.resolution_w, img.textures.resolution_h, "Ulala");
	ft_init_images(&img);
	init_plr(&img);
	// make_image(&img);
	mlx_hook(img.win, 2, 1L<<0, ft_key_press, &img);
	mlx_loop_hook(img.mlx, make_image, &img);
	mlx_hook(img.win, 3, 1L<<1, ft_key_release, &img);
	mlx_loop(img.mlx);
	return 0;
}