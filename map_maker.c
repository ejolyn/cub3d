/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:47:56 by ejolyn            #+#    #+#             */
/*   Updated: 2020/12/20 14:53:35 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**make_map(t_list **head, int size)
{
	char	**map = ft_calloc(size + 1, sizeof(char *));
	int		i = -1;
	size_t	max = 0;
	// char	**trans_map;
	t_list	*tmp = *head;

	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
	}
	map[++i] = NULL;
	// trans_map = map_trans(map, max, size);
	// free (map);
	return (map);
}

char **map_trans(char **map, int max_len, int size)
{
	char **map_transp;
	int i = 0;
	int j = 0;

	map_transp = (char **)malloc((max_len + 1) * sizeof(char *));
	while (j < max_len)
	{
		map_transp[j] = (char *)malloc(size + 1);
		while (i < size)
		{
			if (j < (int)ft_strlen(map[i]))
				map_transp[j][i] = map[i][j];
			else
				map_transp[j][i] = '0';
			i++;
		}
		map_transp[j][i] = '\0';
		j++;
		i = 0;
	}
	map_transp[max_len] = NULL;
	return (map_transp);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_square(t_data *img, int i, int j)
{
	int i2 = i * SCALE_MAP;
	int j2 = j * SCALE_MAP;

	while (i2 < (i + 1) * SCALE_MAP)
	{
		j2 = j * SCALE_MAP;
		while (j2 < (j + 1) * SCALE_MAP)
		{
			my_mlx_pixel_put(img, i2, j2, img->color);
			j2++;
		}
		i2++;
	}
}

void draw_map(t_data *img, char **map)
{
	int i = 0;
	int k = 0;
	int j = 0;

	while (map[i] != NULL)
	{
		k = ft_strlen(map[i]);
		while (j < k)
		{
			if (map[i][j] == '1')
				img->color = 0x0000C8C8;
			else if (map[i][j] == 'N')
			{
				j++;
				continue ;
			}
			else if (map[i][j] == '2')
				img->color = 0x0000C800;
			else
				img->color = 0x00000000;
			draw_square(img, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void find_player(t_data *img)
{
	int i = 0;
	int k = 0;
	int j = 0;
	t_player *plr = (t_player*)malloc(sizeof(t_player*));
	img->player = plr;

	while (img->map[i] != NULL)
	{
		k = ft_strlen(img->map[i]);
		while (j < k)
		{
			if (img->map[i][j] == 'N')
			{
				img->color = 0x0000C800;
				img->player->x = i;
				img->player->y = j;
				img->map[i][j] = 0;
				j++;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}