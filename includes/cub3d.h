/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:24:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/25 16:58:12 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_asset
{
    char    ***split_line;
	void	*walls[4];
    int		floor;
    char    *ceiling;
}				t_asset;

typedef struct s_map
{
    int         total_line;
	int			row;
	int			col;
	int			pixel;
	int			width;
	int			height;
	char		**info;
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

void	read_map(t_game *g, char *f_name);
void	get_info(t_game *g, char *f_name);

/* utils.c */
void	*path2img(void *mlx, char *path);
void	error_msg(void);

/* get_hex_color.c */
char    *int_to_hex_color(char **color_2d);
#endif