/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:16:55 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/24 21:51:53 by hyeonble         ###   ########.fr       */
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

int	is_collision(t_map *map, double x, double y)
{
	return (map->map_2d[(int)y][(int)x] == '1');
}

int	check_collision_with_radius(t_map *map, double new_x, double new_y)
{
	if (is_collision(map, new_x + PLAYER_RADIUS, new_y + PLAYER_RADIUS) ||
		is_collision(map, new_x - PLAYER_RADIUS, new_y + PLAYER_RADIUS) ||
		is_collision(map, new_x + PLAYER_RADIUS, new_y - PLAYER_RADIUS) ||
		is_collision(map, new_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS))
	{
		return (1);
	}
	return (0);
}
void	update_vertical_pos(t_map *map, t_player *player, int dir)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos_x + player->dir_x * MOVE_SPEED * dir;
	new_pos_y = player->pos_y + player->dir_y * MOVE_SPEED * dir;
	if (!check_collision_with_radius(map, new_pos_x, player->pos_y))
		player->pos_x = new_pos_x;
	if (!check_collision_with_radius(map, player->pos_x, new_pos_y))
		player->pos_y = new_pos_y;
}

void	update_horizontal_pos(t_map *map, t_player *player, t_ray *ray, int dir)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos_x + ray->plane_x * MOVE_SPEED * dir;
	new_pos_y = player->pos_y + ray->plane_y * MOVE_SPEED * dir;
	if (!check_collision_with_radius(map, new_pos_x, player->pos_y))
		player->pos_x = new_pos_x;
	if (!check_collision_with_radius(map, player->pos_x, new_pos_y))
		player->pos_y = new_pos_y;
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
