/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:24:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/09/24 21:45:52 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define WINDOW_W 1920
# define WINDOW_H 1080

# define WALL_X 0
# define WALL_Y 1

# define KEYPRESS 02
# define DESTROYNOTIFY 17

# define COLOR_BLACK 0X00000000

# define MOVE_SPEED 0.2
# define ROTATE_SPEED 0.2
# define PLAYER_RADIUS 0.1
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l;
	int		endian;
}				t_image;

typedef struct s_asset
{
	t_image			texture[4];
    int				floor_color;
    int				ceiling_color;
}				t_asset;

typedef struct s_map
{
	int			row;
	int			col;
	int			pixel;
	int			width;
	int			height;
	char		**map_2d;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_ray
{
	int		step_x;
	int		step_y;
	int 	map_x;
	int		map_y;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	camera_y;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_draw
{
	int		draw_start;
	int		draw_end;
	int		texnum;
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;
	double	wall_x;
	double	tex_pos;
}	t_draw;

typedef struct s_game
{
	int			w;
	int			h;
	int			frame;
	int			cnt_move;
	void		*mlx;
	void		*win;
	t_image		image;
	t_map		map;
	t_asset		asset;
	t_player	player;
	t_ray		ray;
	t_draw		draw;
}				t_game;


/* parsing_map.c */
void	get_map_info(t_game *g, int fd, int *map_start);
void	get_map(t_game *g, char *f_name, int map_start);

/* valid_map.c */
void	valid_map(t_game *g);

/* print.c */
void	print_player(t_game *g);
void	print_identifier(t_game *g);
void	print_map(t_game *g);

void	read_map(t_game *g, char *f_name);
void	get_info(t_game *g, char *f_name);

/* utils.c */
void	*xpmpath_to_img(void *mlx, char *path);
void	error_msg(void);
int		pass_line_before_map(char *f_name, int map_start);

/* get_hex_color.c */
char    *int_to_hex_color(char **color_2d);
int		combine_color(char **color_2d);

void	put_pixel_to_image(t_image *image, int x, int y, int color);
void	fill_black(t_image *image);
void	init_player(t_map *map, t_player *player);
void	init_ray(t_map *map, t_ray *ray);
void	set_ray(t_player *player, t_ray *ray, int x);

void	draw(t_game *game);

int	is_collision(t_map *map, double x, double y);
int	check_collision_with_radius(t_map *map, double new_x, double new_y);
void	update_direction(t_player *player, t_ray *ray, double theta);
void	update_vertical_pos(t_map *map, t_player *player, int dir);
void	update_horizontal_pos(t_map *map, t_player *player, t_ray *ray, int dir);
void	move_player(int keycode, t_game *game);
void	rotate_player(int keycode, t_game *game);


int	terminate(t_game *game);
int	handle_keypress(int	keycode, t_game *game);
/* get_fc_color.c */
void	count_comma(char *s);
char	*remove_space(char *s, int idx);

#endif
