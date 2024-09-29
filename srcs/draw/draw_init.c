/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:07:56 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/29 18:11:41 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_map *map, t_player *player)
{
	player->pos_x = (double)map->player_x;
	player->pos_y = (double)map->player_y;
	if (map->player_dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
	if (map->player_dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	if (map->player_dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	if (map->player_dir == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
}

void	init_ray(t_map *map, t_ray *ray)
{
	if (map->player_dir == 'N')
	{
		ray->plane_x = 0.66;
		ray->plane_y = 0.0;
	}
	if (map->player_dir == 'S')
	{
		ray->plane_x = -0.66;
		ray->plane_y = 0.0;
	}
	if (map->player_dir == 'W')
	{
		ray->plane_x = 0.0;
		ray->plane_y = -0.66;
	}
	if (map->player_dir == 'E')
	{
		ray->plane_x = 0.0;
		ray->plane_y = 0.66;
	}
}

void	set_ray(t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_W - 1;
	ray->raydir_x = player->dir_x + ray->plane_x * ray->camera_x;
	ray->raydir_y = player->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->raydir_x)
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	else
		ray->deltadist_x = 1e30;
	if (ray->raydir_y)
		ray->deltadist_y = fabs(1 / ray->raydir_y);
	else
		ray->deltadist_y = 1e30;
	set_sidedist(player, ray);
}

void	set_sidedist(t_player *player, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}
