/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:24:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/30 21:58:37 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

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

typedef struct s_asset
{
	void	*wall_texture[4];
    int		floor_color;
    int		ceiling_color;
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

typedef struct s_game
{
	int			w;
	int			h;
	int			frame;
	int			cnt_move;
	void		*mlx;
	void		*win;
	t_map		map;
	t_asset		asset;
	t_player	player;
	t_ray		ray;
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
void	*path2img(void *mlx, char *path);
void	error_msg(void);
int		pass_line_before_map(char *f_name, int map_start);

/* get_hex_color.c */
char    *int_to_hex_color(char **color_2d);
int		combine_color(char **color_2d);


void	init_player(t_map *map, t_player *player);
void	init_ray(t_map *map, t_ray *ray);
void	set_ray(t_player *player, t_ray *ray, int x);
void	calc_perp_wall_dist(t_ray *ray, t_player *player, int side);
void	draw_vertical_line(t_game *game, int x, int side);
void	draw(t_game *game);

/* get_fc_color.c */
void	count_comma(char *s);
char	*remove_space(char *s, int idx);
#endif
