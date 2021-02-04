/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:47:56 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/03 18:31:13 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**make_map(t_list **head, int size)
{
	char	**map = ft_calloc(size + 1, sizeof(char *));
	int		i = -1;
	// size_t	max = 0;
	t_list	*tmp = *head;

	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
		// if (ft_strlen(map[i]) > max)
		// 	max = ft_strlen(map[i]);
	}
	map[++i] = NULL;
	return (map);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

unsigned int my_mlx_get_color(t_images *img, int x, int y)
{
	unsigned int color;

	color = *(int *)(img->addr + ((x + (y * img->textureWidth)) * (img->bits_per_pixel / 8)));
	return (color);
} 

void find_player(t_data *img)
{
	int i = 0;
	int k = 0;
	int j = 0;
	t_player *plr = (t_player*)malloc(sizeof(t_player*));
	img->player = *plr;

	while (img->map[i] != NULL)
	{
		k = ft_strlen(img->map[i]);
		while (j < k)
		{
			if (img->map[i][j] == 'N')
			{
				img->player.x = i;
				img->player.y = j;
				img->map[i][j] = '0';
				j++;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}