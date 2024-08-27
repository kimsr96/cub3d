/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:09:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/27 15:43:29 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	surrounded_walls(t_game *g, char **map)
{
	size_t	x;
	size_t	y;

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
				else if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					error_msg();
				else if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					error_msg();
			}
			x++;
		}
		y++;
	}
}

void	valid_map(t_game *g)
{
	char	**map;

	map = g->map.map_2d;
	surrounded_walls(g, map);
}
