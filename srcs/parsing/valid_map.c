/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:09:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/10/08 21:18:08 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_surrounded_walls(t_game *g, char **map)
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

void	input_info(t_game *g, char **map, int x, int y)
{
	g->map.player_x = x;
	g->map.player_y = y;
	g->map.player_dir = map[y][x];
	map[y][x] = '0';
}

void	get_player_info(t_game *g, char **map)
{
	int	x;
	int	y;
	int	character_direction;

	y = -1;
	character_direction = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0' || map[y][x] == '1' || map[y][x] == ' ')
				continue ;
			if (character_direction == 0 && (map[y][x] == 'E' || \
			map[y][x] == 'W' || map[y][x] == 'S' || map[y][x] == 'N'))
			{
				input_info(g, map, x, y);
				character_direction = 1;
			}
			else if (character_direction)
				error_msg();
			else
				error_msg();
		}
	}
}

void	check_valid_map(t_game *g)
{
	char	**map;

	map = g->map.map_2d;
	check_surrounded_walls(g, map);
	get_player_info(g, map);
}
