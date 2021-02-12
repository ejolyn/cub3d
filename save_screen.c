/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:28:57 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 13:35:39 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_write_header(int fd, t_data *img)
{
	int str;

	write(fd, "BM", 2);
	str = 54 + img->textures.resolution_w *
		img->textures.resolution_h * img->bits_per_pixel / 8;
	write(fd, &str, 4);
	str = 0;
	write(fd, &str, 2);
	write(fd, &str, 2);
	str = 54;
	write(fd, &str, 4);
	str = 40;
	write(fd, &str, 4);
	write(fd, &img->textures.resolution_w, 4);
	write(fd, &img->textures.resolution_h, 4);
	str = 1;
	write(fd, &str, 2);
	write(fd, &img->bits_per_pixel, 2);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 24);
}

void	ft_screen_to_bmp(t_data *img)
{
	int		fd;
	int		i;
	char	*str;

	i = img->textures.resolution_h - 1;
	str = (char *)"screenshot.bmp";
	fd = open(str, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		ft_error(img, "Fail to create screenshot");
	ft_write_header(fd, img);
	while (i >= 0)
	{
		write(fd, (img->addr + i * img->line_length),
			(img->textures.resolution_w * img->bits_per_pixel / 8));
		i--;
	}
	if (close(fd) < 0)
		ft_error(img, "Something went wrong while closing screenshot");
	exit(0);
}

void	check_free(t_data *img)
{
	int i;

	i = -1;
	if (img)
	{
		if (img->textures.south)
			free(img->textures.south);
		if (img->textures.north)
			free(img->textures.north);
		if (img->textures.west)
			free(img->textures.west);
		if (img->textures.east)
			free(img->textures.east);
		if (img->spr_buffer)
			free(img->spr_buffer);
		if (img->map)
		{
			while (img->map[++i])
				free(img->map[i]);
			free(img->map);
		}
		free(img);
	}
}

int		ft_texture_side(t_data *img, int side)
{
	int texnum;

	texnum = 0;
	if (img->mapx < img->player.x && side == 0)
		texnum = 0;
	if (img->mapx > img->player.x && side == 0)
		texnum = 1;
	if (img->mapy > img->player.y && side == 1)
		texnum = 3;
	if (img->mapy < img->player.y && side == 1)
		texnum = 2;
	return (texnum);
}
