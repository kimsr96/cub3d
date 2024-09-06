/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:41:40 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/06 17:47:27 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_perp_wall_dist(t_ray *ray, t_player *player, int side)
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

static void	draw_ceiling_and_floor(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->draw.draw_start)
	{
		put_pixel_to_image(&game->image, x, y, game->asset.ceiling_color);
		y++;
	}
	y = game->draw.draw_end;
	while (y < WINDOW_H)
	{
		put_pixel_to_image(&game->image, x, y, game->asset.floor_color);
		y++;
	}
}

static double	get_wall_x(t_game *game, int side)
{
	t_player	player;
	t_ray		ray;
	double		wall_x;

	player = game->player;
	ray = game->ray;
	if (side == WALL_X)
		wall_x = player.pos_y + ray.perp_wall_dist * ray.raydir_y;
	else
		wall_x = player.pos_x + ray.perp_wall_dist * ray.raydir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_tex_x(t_game *game, double wall_x, int side)
{
	int	tex_x;

	tex_x = (int)(wall_x * 64);
	if (side == WALL_X && game->ray.raydir_x > 0)
		tex_x = 64 - tex_x - 1;
	if (side == WALL_Y && game->ray.raydir_y < 0)
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

static unsigned int	get_tex_color(t_game *game)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*tex_ptr;
	char	*texture_data;

	texture_data = mlx_get_data_addr(game->asset.wall_texture[game->draw.texnum]\
	, &bpp, &size_line, &endian);
	tex_ptr = texture_data + (game->draw.tex_y * size_line + (game->draw.tex_x * (bpp / 8)));
	return (*(unsigned int *)tex_ptr);
}

static void	draw_vertical_line(t_game *game, int x, int side)
{
	int	y;

	game->draw.wall_x = get_wall_x(game, side);
	game->draw.tex_x = get_tex_x(game, game->draw.wall_x, side);
	game->draw.step = 1.0 * 64 / (game->draw.draw_end - game->draw.draw_start);
	game->draw.tex_pos = (game->draw.draw_start - WINDOW_H / 2 + \
	(game->draw.draw_end - game->draw.draw_start) / 2) * game->draw.step;
	y = game->draw.draw_start;
	while (y < game->draw.draw_end)
	{
		game->draw.tex_y = (int)game->draw.tex_pos & (64 - 1);
		game->draw.tex_pos += game->draw.step;
		game->draw.color = get_tex_color(game);
		if (side == WALL_Y)
			game->draw.color = (game->draw.color >> 1) & 8355711;
		put_pixel_to_image(&game->image, x, y, game->draw.color);
		y++;
	}
}

static int	select_texture(t_game *game, int side)
{
	if (side == WALL_X)
	{
		if (game->ray.raydir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (game->ray.raydir_y > 0)
			return (1);
		else
			return (0);
	}
}

static void	raycast(t_game *game, int x)
{
	int	hit;
	int	side;
	int	line_height;

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
	game->draw.texnum = select_texture(game, side);
	line_height = (int)(WINDOW_H / game->ray.perp_wall_dist);
	game->draw.draw_start = -line_height / 2 + WINDOW_H / 2;
	if (game->draw.draw_start < 0)
		game->draw.draw_start = 0;
	game->draw.draw_end = line_height / 2 + WINDOW_H / 2;
	if (game->draw.draw_end >= WINDOW_H)
		game->draw.draw_end = WINDOW_H - 1;
	calc_perp_wall_dist(&game->ray, &game->player, side);
	draw_ceiling_and_floor(game, x);
	draw_vertical_line(game, x, side);
}

void	draw(t_game *game)
{
	int	x;

	fill_black(&game->image);
	x = 0;
	while (x < WINDOW_W)
	{
		set_ray(&game->player, &game->ray, x);
		raycast(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0 , 0);
}
