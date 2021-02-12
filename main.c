/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:49:32 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:08:02 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		validator_map(t_data *img, int x, int y)
{
	if (img->map[x] == NULL)
		return (0);
	if (img->map[x][y] == ' ' || img->map[x][y] == '\0' ||
		x < 0 || y < 0 || x > img->map_max_size)
		return (0);
	if (img->map[x][y] == '1' || img->map[x][y] == '3' || img->map[x][y] == '5')
		return (1);
	if (img->map[x][y] == '0')
		img->map[x][y] = '3';
	if (img->map[x][y] == '2')
		img->map[x][y] = '5';
	return (validator_map(img, x + 1, y) && validator_map(img, x, y + 1)
			&& validator_map(img, x - 1, y) && validator_map(img, x, y - 1));
}

int		make_image(t_data *img)
{
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, img->textures.resolution_w,
		img->textures.resolution_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	processor_move_player(img);
	processor_look_player(img);
	raycast_main(img);
	if (img->save == 1)
		ft_screen_to_bmp(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (1);
}

void	map_rehab_after_validation(t_data *img)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (img->map[i] != NULL)
	{
		while (img->map[i][j] != '\0')
		{
			if (img->map[i][j] == '3')
				img->map[i][j] = '0';
			if (img->map[i][j] == '5')
				img->map[i][j] = '2';
			j++;
		}
		j = 0;
		i++;
	}
}

void	mlx(t_data *img, char *argv)
{
	int		fd;

	fd = 0;
	init(img);
	if (check_argv(argv) || ((fd = open(argv, O_RDONLY)) < 0))
		ft_error(img, "Can't open cub file");
	img->map = parser(fd, img);
	find_player(img);
	find_sprites(img, 0);
	if (!(full_validator(img, (int)(img->player.x - 0.5),
		(int)(img->player.y - 0.5))))
		ft_error(img, "Invalid map");
	map_rehab_after_validation(img);
	img->mlx = mlx_init();
	if (img->save != 1)
		img->win = mlx_new_window(img->mlx,
			img->textures.resolution_w, img->textures.resolution_h, "Ulala");
	ft_init_images(img);
	init_plr(img);
	make_image(img);
	mlx_hook(img->win, 2, 1L << 0, &ft_key_press, img);
	mlx_hook(img->win, 17, 1L << 17, ft_close_programm, img);
	mlx_loop_hook(img->mlx, make_image, img);
	mlx_hook(img->win, 3, 1L << 1, &ft_key_release, img);
	mlx_loop(img->mlx);
}

int		main(int argc, char **argv)
{
	t_data	*img;

	img = NULL;
	if (!(img = (t_data *)malloc(sizeof(t_data))))
		ft_error(img, "Trouble with malloc");
	img->save = 0;
	if (argc == 2)
		mlx(img, argv[1]);
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
	{
		img->save = 1;
		mlx(img, argv[1]);
	}
	else
		ft_error(img, "Wrong number of arguments or wrong save flag");
	return (0);
}
