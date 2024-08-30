/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:41:40 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/30 21:45:01 by hyeonble         ###   ########.fr       */
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
	// printf("playerdirx: %f, playerdiry: %f", player->dir_x, player->dir_y);
	ray->raydir_x = player->dir_x + ray->plane_x * ray->camera_x;
	ray->raydir_y = player->dir_y + ray->plane_y * ray->camera_x;
	// printf("raydirx: %f, raydiry: %f\n", ray->raydir_x, ray->raydir_y);
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

void	calc_perp_wall_dist(t_ray *ray, t_player *player, int side)
{
	if (side == WALL_X)
	{
		ray->perp_wall_dist = (ray->map_x - player->pos_x + \
		(1 - ray->step_x) / 2) / ray->raydir_x;
	}
	else if (side == WALL_Y)
	{
		ray->perp_wall_dist = (ray->map_y - player->pos_y + \
		(1 - ray->step_y) / 2) / ray->raydir_y;
	}
}

void	draw_vertical_line(t_game *game, int x, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;

	line_height = (int)(WINDOW_H / game->ray.perp_wall_dist);
	draw_start = -line_height / 2 + WINDOW_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_H / 2;
	if (draw_end >= WINDOW_H)
		draw_end = WINDOW_H - 1;
	color = 0x0000FF;
	if (side == WALL_Y)
		color = color / 2;
	y = 0;
	while (y < draw_start)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, game->asset.ceiling_color);
		y++;
	}
	while (y <= draw_end)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		y++;
	}
	while (y < WINDOW_H)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, game->asset.floor_color);
		y++;
	}
}

void	draw(t_game *game)
{
	int	x;
	int	hit;
	int	side;

	x = 0;
	init_player(&game->map, &game->player);
	init_ray(&game->map, &game->ray);
	while (x < WINDOW_W)
	{
		set_ray(&game->player, &game->ray, x);
		hit = 0;
		while (!hit)
		{
			if (game->ray.sidedist_x < game->ray.sidedist_y)
			{
				game->ray.sidedist_x += game->ray.deltadist_x;
				game->ray.map_x += game->ray.step_x;
				side = WALL_X;
			}
			else
			{
				game->ray.sidedist_y += game->ray.deltadist_y;
				game->ray.map_y += game->ray.step_y;
				side = WALL_Y;
			}
			if (game->ray.map_x >= 0 && game->ray.map_x < game->map.col && \
			game->ray.map_y >= 0 && game->ray.map_y < game->map.row) 
			{
				if (game->map.map_2d[game->ray.map_y][game->ray.map_x] > '0')
					hit = 1;
			}
			else
				hit = 1;
		}
		calc_perp_wall_dist(&game->ray, &game->player, side);
		draw_vertical_line(game, x, side);
		x++;
	}
}
