/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:33:16 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 11:46:05 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	processor_look_player(t_data *img)
{
	float copydirectx;
	float copyplanex;
	float rotate;

	copydirectx = img->player.directx;
	copyplanex = img->player.planex;
	rotate = ROTATE_SPEED;
	if (img->rotate == -1)
		rotate = -ROTATE_SPEED;
	if (img->rotate == 1 || img->rotate == -1)
	{
		img->player.directx = copydirectx * cos(rotate) -
			img->player.directy * sin(rotate);
		img->player.directy = copydirectx * sin(rotate) +
			img->player.directy * cos(rotate);
		img->player.planex = copyplanex * cos(rotate) -
			img->player.planey * sin(rotate);
		img->player.planey = copyplanex * sin(rotate) +
			img->player.planey * cos(rotate);
	}
}

void	processor_move_player(t_data *img)
{
	if (img->move_w == 1)
	{
		if (img->map[(int)(img->player.x + img->player.directx * MOVE_SPEED)]
		[(int)(img->player.y)] == '0')
			img->player.x += img->player.directx * MOVE_SPEED;
		if (img->map[(int)(img->player.x)]
		[(int)(img->player.y + img->player.directy * MOVE_SPEED)] == '0')
			img->player.y += img->player.directy * MOVE_SPEED;
	}
	if (img->move_s == 1)
	{
		if (img->map[(int)(img->player.x - img->player.directx * MOVE_SPEED)]
		[(int)(img->player.y)] == '0')
			img->player.x -= img->player.directx * MOVE_SPEED;
		if (img->map[(int)(img->player.x)]
		[(int)(img->player.y - img->player.directy * MOVE_SPEED)] == '0')
			img->player.y -= img->player.directy * MOVE_SPEED;
	}
	processor_strafe(img);
}

void	processor_strafe(t_data *img)
{
	if (img->move_a == 1)
	{
		if (img->map[(int)(img->player.x - img->player.planex * MOVE_SPEED)]
		[(int)(img->player.y)] == '0')
			img->player.x -= img->player.planex * MOVE_SPEED;
		if (img->map[(int)(img->player.x)]
		[(int)(img->player.y - img->player.planey * MOVE_SPEED)] == '0')
			img->player.y -= img->player.planey * MOVE_SPEED;
	}
	if (img->move_d == 1)
	{
		if (img->map[(int)(img->player.x + img->player.planex * MOVE_SPEED)]
		[(int)(img->player.y)] == '0')
			img->player.x += img->player.planex * MOVE_SPEED;
		if (img->map[(int)(img->player.x)]
		[(int)(img->player.y + img->player.planey * MOVE_SPEED)] == '0')
			img->player.y += img->player.planey * MOVE_SPEED;
	}
}

int		ft_key_press(int keycode, t_data *img)
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
		img->rotate = 1;
	if (keycode == RIGHT)
		img->rotate = -1;
	return (0);
}

int		ft_key_release(int keycode, t_data *img)
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
		img->rotate = 0;
	if (keycode == RIGHT)
		img->rotate = 0;
	return (0);
}
