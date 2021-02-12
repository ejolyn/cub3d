/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:47:56 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:21:23 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_dobivka(t_data *img, char **map, size_t max)
{
	int		i;
	int		k;
	char	*line;

	i = -1;
	k = 0;
	line = NULL;
	while (map[++i] != NULL)
	{
		k = 0;
		if (!(line = (char *)malloc(max + 1)))
			ft_error(img, "Trouble with malloc");
		while (map[i][k] != '\0')
		{
			line[k] = map[i][k];
			k++;
		}
		while (k < (int)max)
			line[k++] = ' ';
		line[k] = '\0';
		map[i] = line;
	}
	return (map);
}

char	**make_map(t_list **head, int size, t_data *img)
{
	char	**map;
	int		i;
	size_t	max;
	t_list	*tmp;

	i = -1;
	max = 0;
	tmp = *head;
	if (!(map = malloc((size + 1) * sizeof(char *))))
		ft_error(img, "Trouble with malloc");
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
	}
	if (map[i][0] == '\0')
		ft_error(img, "Invalid map information");
	map[++i] = NULL;
	map = map_dobivka(img, map, max);
	img->map_max_size = (int)max;
	return (map);
}

void	helper_find_player_and_sprites(t_data *img, int i, int j)
{
	if (img->map[i][j] != 'N' && img->map[i][j] != 'S' &&
		img->map[i][j] != 'W' && img->map[i][j] != 'E'
		&& img->map[i][j] != '0' && img->map[i][j] != '1' &&
			img->map[i][j] != '2' && img->map[i][j] != ' ')
		ft_error(img, "Invalid map - wrong symbols in map");
	if (img->map[i][j] == 'N' || img->map[i][j] == 'S' ||
		img->map[i][j] == 'W' || img->map[i][j] == 'E')
	{
		if (img->player.x != -1 || img->player.y != -1)
			ft_error(img, "Double player");
		img->player.x = i + 0.5;
		img->player.y = j + 0.5;
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

void	find_player(t_data *img)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	img->sprite.numofsprites = 0;
	img->player.orientation = 0;
	img->player.x = -1;
	img->player.y = -1;
	while (img->map[i] != NULL)
	{
		j = ft_strlen(img->map[i]);
		while (--j >= 0)
			helper_find_player_and_sprites(img, i, j);
		i++;
	}
	if (img->player.x == -1 && img->player.y == -1)
		ft_error(img, "Where is the player?");
}

void	find_sprites(t_data *img, int i)
{
	t_individual	*spr_array;
	int				j;
	int				l;

	j = 0;
	l = 0;
	if (!(spr_array = (t_individual *)malloc(sizeof(t_individual)
		* img->sprite.numofsprites)))
		ft_error(img, "Trouble with malloc");
	while (img->map[i] != NULL)
	{
		j = ft_strlen(img->map[i]);
		while (--j >= 0)
		{
			if (img->map[i][j] == '2')
			{
				spr_array[l].x = i + 0.5;
				spr_array[l].y = j + 0.5;
				l++;
			}
		}
		i++;
	}
	img->spr_array = spr_array;
}
