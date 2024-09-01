/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:16:55 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/01 20:53:22 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_direction(t_player *player, t_ray *ray, double theta)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir_x;
	old_planex = ray->plane_x;
	player->dir_x = player->dir_x * cos(theta) - player->dir_y * sin(theta);
	player->dir_y = old_dirx * sin(theta) + player->dir_y * cos(theta);
	ray->plane_x = ray->plane_x * cos(theta) - ray->plane_y * sin(theta);
	ray->plane_y = old_planex * sin(theta) + ray->plane_y * cos(theta);
}

void	update_position(t_map *map, t_player *player, t_ray *ray)
{
	double	delta_x;
	double	delta_y;

	delta_x = player->dir_x * MOVE_SPEED;
	delta_y = player->dir_y * MOVE_SPEED;
	if (map->map_2d[(int)player->pos_y][(int)(player->pos_x + delta_x)])
		player->pos_x += delta_x;
	if (map->map_2d[(int)(player->pos_y + delta_y)][(int)player->pos_x])
		player->pos_y += delta_y;
}
