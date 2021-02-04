/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:49:32 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/04 10:27:11 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void make_image(t_data *img)
{
	mlx_clear_window(img->mlx, img->win);
	img->img = mlx_new_image(img->mlx, img->textures.resolution_w, img->textures.resolution_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
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

void three_d(t_data *img)
{
	int x = 0;
	short side = 0;
	
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
		}
		if (side == 1)
			img->player.perpWallDist = (img->mapY - img->player.y + (1 - img->player.stepY) / 2) / img->player.raydirectY;
		else
			img->player.perpWallDist = (img->mapX - img->player.x + (1 - img->player.stepX) / 2) / img->player.raydirectX;
		img->player.line_h = (int)(img->textures.resolution_h / img->player.perpWallDist);
		ft_draw_line(img, x, side);
	}
}

void processor_move_player(int keycode, t_data *img)
{
	if (keycode == W || keycode == UP)
	{
		if (img->map[(int)(img->player.x + img->player.directX * MOVE_SPEED * 2)][(int)(img->player.y)] == '0')
			img->player.x += img->player.directX * MOVE_SPEED;
		if (img->map[(int)(img->player.x)][(int)(img->player.y + img->player.directY * MOVE_SPEED * 2)] == '0')
			img->player.y += img->player.directY * MOVE_SPEED;
	}
	if (keycode == S || keycode == DOWN)
	{
		if (img->map[(int)(img->player.x - img->player.directX * MOVE_SPEED * 2)][(int)(img->player.y)] == '0')
			img->player.x -= img->player.directX * MOVE_SPEED;
		if (img->map[(int)(img->player.x)][(int)(img->player.y - img->player.directY * MOVE_SPEED * 2)] == '0')
			img->player.y -= img->player.directY * MOVE_SPEED;
	}
	// if (keycode == A)
	// {
	// 	img->player.x -= img->player.directX * MOVE_SPEED;
	// 	img->player.y += img->player.directY * MOVE_SPEED;
	// }
	// if (keycode == D)
	// {
	// 	img->player.x += img->player.directX * MOVE_SPEED;
	// 	img->player.y += img->player.directY * MOVE_SPEED;
	// }
	make_image(img);
	three_d(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return;
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
	int texX = (int)(wallX * (double)(img->images[texNum].textureHeight));
	if (side == 0 && img->player.raydirectX > 0)
		texX = img->images[texNum].textureWidth - texX - 1;
	if (side == 1 && img->player.raydirectX < 0)
		texX = img->images[texNum].textureWidth - texX - 1;
	
	double step = 1.0 * img->images[texNum].textureHeight / img->player.line_h;
	line_start = (line_start < 0) ? 0 : line_start;
	line_end = (line_end >= img->textures.resolution_h) ? img->textures.resolution_h - 1: line_end;
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

void processor_look_player(int keycode, t_data *img)
{
	float copydirectX = img->player.directX;
	float copyplaneX = img->player.planeX;
	if (keycode == LEFT)
	{
		img->player.directX = copydirectX * cos(ROTATE_SPEED) - img->player.directY * sin(ROTATE_SPEED);
		img->player.directY = copydirectX * sin(ROTATE_SPEED) + img->player.directY * cos(ROTATE_SPEED);
		img->player.planeX = copyplaneX * cos(ROTATE_SPEED) - img->player.planeY * sin(ROTATE_SPEED);
		img->player.planeY = copyplaneX * sin(ROTATE_SPEED) + img->player.planeY * cos(ROTATE_SPEED);
	}
	if (keycode == RIGHT)
	{
		img->player.directX = copydirectX * cos(-ROTATE_SPEED) - img->player.directY * sin(-ROTATE_SPEED);
		img->player.directY = copydirectX * sin(-ROTATE_SPEED) + img->player.directY * cos(-ROTATE_SPEED);
		img->player.planeX = copyplaneX * cos(-ROTATE_SPEED) - img->player.planeY * sin(-ROTATE_SPEED);
		img->player.planeY = copyplaneX * sin(-ROTATE_SPEED) + img->player.planeY * cos(-ROTATE_SPEED);
	}
	make_image(img);
	three_d(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return;
}

int			close_win(int keycode, t_data *img)
{
	if (keycode == ESC)
	{
    	mlx_destroy_window(img->mlx, img->win);
		exit(0);
	}
	else if (keycode == W || keycode == A || keycode == S || keycode == D || keycode == UP || keycode == DOWN)
		processor_move_player(keycode, img);
	else if (keycode == LEFT || keycode == RIGHT)
		processor_look_player(keycode, img);
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
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.textures.resolution_w, img.textures.resolution_h, "Ulala");
	ft_init_images(&img);
	make_image(&img);
	init_plr(&img);
	three_d(&img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_destroy_image(img.mlx, img.img);
	mlx_hook(img.win, 2, 1L<<0, close_win, &img);
	mlx_loop(img.mlx);
	return 0;
}