/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:16:53 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/29 18:10:57 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_collision(t_map *map, double x, double y)
{
	return (map->map_2d[(int)y][(int)x] == '1');
}

int	check_collision_with_radius(t_map *map, double new_x, double new_y)
{
	if (is_collision(map, new_x + PLAYER_RADIUS, new_y + PLAYER_RADIUS) \
		|| is_collision(map, new_x - PLAYER_RADIUS, new_y + PLAYER_RADIUS) \
		|| is_collision(map, new_x + PLAYER_RADIUS, new_y - PLAYER_RADIUS) \
		|| is_collision(map, new_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS))
	{
		return (1);
	}
	return (0);
}
