/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:47:56 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/06 17:05:16 by ejolyn           ###   ########.fr       */
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

unsigned int my_mlx_get_color_sprite(t_sprite *img, int x, int y)
{
	unsigned int color;

	color = *(int *)(img->addr + ((x + (y * img->textureWidth)) * (img->bits_per_pixel / 8)));
	return (color);
} 

unsigned int my_mlx_get_color(t_images *img, int x, int y)
{
	unsigned int color;

	color = *(int *)(img->addr + ((x + (y * img->textureWidth)) * (img->bits_per_pixel / 8)));
	return (color);
} 

void helper_find_player_and_sprites(t_data *img, int i, int j)
{
	if (img->map[i][j] == 'N' || img->map[i][j] == 'S' || img->map[i][j] == 'W' || img->map[i][j] == 'E')
	{
		img->player.x = i;
		img->player.y = j;
		if (img->map[i][j] == 'N')
			img->player.orientation = 'N';
		if (img->map[i][j] == 'S')
			img->player.orientation = 'S';
		if (img->map[i][j] == 'W')
			img->player.orientation = 'W';
		if (img->map[i][j] == 'E')
			img->player.orientation = 'E';
		img->map[i][j] = '0';
	}
	if (img->map[i][j] == '2')
		img->sprite.numofsprites++;
}

void find_player(t_data *img)
{
	int i;
	int k;
	int j;
	t_player *plr;
	
	i = 0;
	j = 0;
	k = 0;
	plr = (t_player*)malloc(sizeof(t_player*));
	img->player = *plr;
	img->sprite.numofsprites = 0;
	img->player.orientation = 0;
	while (img->map[i] != NULL)
	{
		k = ft_strlen(img->map[i]);
		while (j < k)
		{
			helper_find_player_and_sprites(img, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void find_sprites(t_data *img)
{
	t_individual *spr_array = (t_individual *)malloc(sizeof(t_individual) * img->sprite.numofsprites);
	int i = 0;
	int k = 0;
	int j = 0;
	int l = 0;
	
	while (img->map[i] != NULL)
	{
		k = ft_strlen(img->map[i]);
		while (j < k)
		{
			if (img->map[i][j] == '2')
			{
				spr_array[l].x = i;
				spr_array[l].y = j;
				l++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	img->spr_array = spr_array;
}