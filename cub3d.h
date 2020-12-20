/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:50:58 by ejolyn            #+#    #+#             */
/*   Updated: 2020/12/20 15:10:46 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_player {
	float		x;
	float		y;
	float		planeX;	// camera plane
	float		planeY;
	float		directX; //direction vector
	float		directY;
	float		cameraX;
	float		raydirectX;
	float		raydirectY;
	int			stepX;
	int			stepY;
	float		sidedistX;
	float		sidedistY;
	float		deltadistX;
	float		deltadistY;
	float		perpWallDist;
	int			line_h;
	float		left;
	float		right;	
}				t_player;

typedef struct	s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;		
	long		color_floor;
	long		color_ceiling;
}				t_textures;

typedef struct  s_data {
    void        *img;
	void		*mlx;
    void		*win;
    char        *addr;
	int			resolution_w;
	int			resolution_h;
	int			color;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			error;
	int			mapX;
	int			mapY;
	// t_textures	*textures;
	t_player	*player;
	char		**map;
}               t_data;

#include <fcntl.h>
#include <mlx.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <math.h>
#include <stdio.h>

# define ESC 53
# define UP	126
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define W 13
# define A 0
# define S 1
# define D 2

# define SCALE_MAP 15
# define MOVE_SPEED 1
# define ROTATE_SPEED 0.3
# define MAP_ERROR 1
# define READ_ERROR 2
# define GAME_ERROR 3

char	**map_trans(char **map, int max_len, int size);
char	**make_map(t_list **head, int size);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_square(t_data *img, int i, int j);
void	draw_map(t_data *img, char **map);
int		close_win(int keycode, t_data *vars);
void	ft_error(t_data *img, char *error);
char	**parser(int fd);
int		validate_map(t_data *img, char **map);
void	processor_move_player(int keycode, t_data *img);
void 	find_player(t_data *img);
void	ft_cast_rays(t_data *data);
void	ft_draw_line(t_data *img, int x, short side);
