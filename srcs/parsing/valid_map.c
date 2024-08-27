/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:09:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/27 17:33:54 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	surrounded_walls(t_game *g, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'E' || map[y][x] == 'W' || \
				map[y][x] == 'S' || map[y][x] == 'N')
			{
				if (x == 0 || x == g->map.col || y == 0 || y == g->map.row - 1)
					error_msg();
				else if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || \
							map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					error_msg();
			}
			x++;
		}
		y++;
	}
}

void	get_player_info(t_game *g, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0' || map[y][x] == '1' || map[y][x] == ' ')
				continue ;
			else if (map[y][x] == 'E' || map[y][x] == 'W' || \
				map[y][x] == 'S' || map[y][x] == 'N')
			{
				g->map.player_x = x;
				g->map.player_y = y;
				g->map.player_dir = map[y][x];
			}
			else
				error_msg();
		}
		y++;
	}
}

void	valid_map(t_game *g)
{
	char	**map;

	map = g->map.map_2d;
	surrounded_walls(g, map);
	get_player_info(g, map);
}
