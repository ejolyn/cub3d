/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:50:58 by ejolyn            #+#    #+#             */
/*   Updated: 2021/02/12 12:40:36 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CUB3D_H
#	define CUB3D_H

#include <fcntl.h>
#include "mlx/mlx.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <math.h>

typedef struct		s_player {
	float			x;
	float			y;
	char			orientation;
	float			planex;
	float			planey;
	float			directx;
	float			directy;
	float			camerax;
	float			raydirectx;
	float			raydirecty;
	int				stepx;
	int				stepy;
	float			sidedistx;
	float			sidedisty;
	float			deltadistx;
	float			deltadisty;
	float			perpwalldist;
	int				line_h;
	float			left;
	float			right;
}					t_player;

typedef struct		s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
	int				resolution_w;
	int				resolution_h;
	int				color_floor;
	int				color_ceiling;
}					t_textures;

typedef struct		s_images
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
	int				texturewidth;
	int				textureheight;
	int				texx;
	int				texy;
}					t_images;

typedef struct		s_individual
{
	double			x;
	double			y;
	int				spriteorder;
	double			spritedistance;
}					t_individual;

typedef struct		s_sprite
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
	int				numofsprites;
	int				texturewidth;
	int				textureheight;
	double			sprx;
	double			spry;
	double			invdet;
	double			transformx;
	double			transformy;
	int				sprscreenx;
	int				sprheight;
	int				drawstarty;
	int				drawendy;
	int				sprwidth;
	int				texx;
	int				texy;
	int				spr_y;
	int				drawstartx;
	int				drawendx;
}					t_sprite;

typedef struct		s_data {
	void			*img;
	void			*mlx;
	void			*win;
	char			*addr;
	int				color;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				error;
	int				mapx;
	int				mapy;
	int				line_start;
	int				line_end;
	double			wallx;
	int				screen_w;
	int				screen_h;
	int				move_w;
	int				move_s;
	int				move_a;
	int				move_d;
	int				rotate;
	int				save;
	int				texnum;
	double			texpos;
	double			step;
	double			*spr_buffer;
	t_textures		textures;
	t_player		player;
	t_images		images[4];
	t_sprite		sprite;
	t_individual	*spr_array;
	char			**map;
	int				map_max_size;
}					t_data;

#define ESC 53
#define UP 126
#define LEFT 123
#define RIGHT 124
#define DOWN 125
#define W 13
#define A 0
#define S 1
#define D 2
#define SCALE_MAP 15
#define MOVE_SPEED 0.1
#define ROTATE_SPEED 0.05

char				**make_map(t_list **head, int size, t_data *img);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_square(t_data *img, int i, int j);
void				draw_map(t_data *img, char **map);
int					close_win(int keycode, t_data *vars);
void				ft_error(t_data *img, char *error);
char				**parser(int fd, t_data *img);
int					validate_map(t_data *img, char **map);
void				processor_move_player(t_data *img);
void				processor_strafe(t_data *img);
void				processor_look_player(t_data *img);
void				find_player(t_data *img);
void				find_sprites(t_data *img, int i);
void				ft_cast_rays(t_data *data);
void				ft_draw_line(t_data *img, int x, int side);
int					validator_map(t_data *img, int x, int y);
char				**map_dobivka(t_data *img, char **map, size_t max);
int					ft_key_press(int keycode, t_data *img);
int					ft_key_release(int keycode, t_data *img);
void				raycast_main(t_data *img);
void				ft_parse_textures(t_data *img, char **texture, char *line);
void				ft_parse_resolution(t_data *img, char *str);
void				ft_parse_color_floor(t_data *img, char *str);
void				ft_parse_color_ceiling(t_data *img, char *str);
unsigned int		my_mlx_get_color(t_images *img, int x, int y);
unsigned int		my_mlx_get_color_sprite(t_sprite *img, int x, int y);
void				ft_write_header(int fd, t_data *img);
void				ft_screen_to_bmp(t_data *img);
void				init(t_data *data);
void				init_plr (t_data *img);
void				ft_init_images(t_data *img);
int					ft_texture_side(t_data *img, int side);
void				ft_bubble_sort_sprites(t_data *img);
void				draw_sprites(t_data *img);
void				calculate_sidedist(t_data *img);
void				ft_draw_floor_ceiling(t_data *img, int x);
int					ft_close_programm(t_data *img);
int					full_validator(t_data *img, int x, int y);
void				check_resol(t_data *img, char *str);
int					check_argv(char *argv);
void				check_free(t_data *img);

#	endif
