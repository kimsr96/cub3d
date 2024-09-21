/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:16:55 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/21 20:16:46 by hyeonble         ###   ########.fr       */
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

void	update_vertical_pos(t_map *map, t_player *player, int dir)
{
	double	delta_x;
	double	delta_y;
	double 	collision_dist;

	delta_x = player->dir_x * MOVE_SPEED * dir;
	delta_y = player->dir_y * MOVE_SPEED * dir;
	collision_dist = 0.5 * dir;
	if (map->map_2d[(int)player->pos_y][(int)(player->pos_x + delta_x + collision_dist)] == '0')
		player->pos_x += delta_x;
	if (map->map_2d[(int)(player->pos_y + delta_y + collision_dist)][(int)player->pos_x] == '0')
		player->pos_y += delta_y;
}

void	update_horizontal_pos(t_map *map, t_player *player, t_ray *ray, int dir)
{
	double	delta_x;
	double	delta_y;
	double	collision_dist;

	delta_x = ray->plane_x * MOVE_SPEED * dir;
	delta_y = ray->plane_y * MOVE_SPEED * dir;
	collision_dist = 0.5 * dir;

	if (map->map_2d[(int)player->pos_y][(int)(player->pos_x + delta_x + collision_dist)] == '0')
		player->pos_x += delta_x;
	if (map->map_2d[(int)(player->pos_y + delta_y + collision_dist)][(int)player->pos_x] == '0')
		player->pos_y += delta_y;
}

void	move_player(int keycode, t_game *game)
{
	if (keycode == 13)
		update_vertical_pos(&(game->map), &(game->player), 1);
	if (keycode == 1)
		update_vertical_pos(&(game->map), &(game->player), -1);
	if (keycode == 0)
		update_horizontal_pos(&(game->map), &(game->player), &(game->ray), -1);
	if (keycode == 2)
		update_horizontal_pos(&(game->map), &(game->player), &(game->ray), 1);
}

void	rotate_player(int keycode, t_game *game)
{
	if (keycode == 123)
		update_direction(&(game->player), &(game->ray), -ROTATE_SPEED);
	if (keycode == 124)
		update_direction(&(game->player), &(game->ray), ROTATE_SPEED);
}
