/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:24:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/27 18:03:41 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define WINDOW_W 
# define WINDOW_H

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
	//t_player	player;
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
#endif


//open
//get texture
//get combine_color
//get s_map
//close