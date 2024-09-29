/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:56:07 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/29 18:07:37 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_hit(t_game *game, int *side, int *hit)
{
	if (game->ray.sidedist_x < game->ray.sidedist_y)
	{
		game->ray.sidedist_x += game->ray.deltadist_x;
		game->ray.map_x += game->ray.step_x;
		*side = WALL_X;
	}
	else
	{
		game->ray.sidedist_y += game->ray.deltadist_y;
		game->ray.map_y += game->ray.step_y;
		*side = WALL_Y;
	}
	if (game->ray.map_x >= 0 && game->ray.map_x < game->map.col && \
	game->ray.map_y >= 0 && game->ray.map_y < game->map.row)
	{
		if (game->map.map_2d[game->ray.map_y][game->ray.map_x] > '0')
			*hit = 1;
	}
	else
		*hit = 1;
}

static void	raycast(t_game *game, int x)
{
	int	hit;
	int	side;
	int	line_height;

	hit = 0;
	while (!hit)
	{
		check_hit(game, &side, &hit);
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

void	draw_ceiling_and_floor(t_game *game, int x)
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

void	draw_vertical_line(t_game *game, int x, int side)
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
		game->draw.color = get_tex_color(game, game->draw.tex_x, \
		game->draw.tex_y);
		if (side == WALL_Y)
			game->draw.color = (game->draw.color >> 1) & 8355711;
		put_pixel_to_image(&game->image, x, y, game->draw.color);
		y++;
	}
}

void	draw(t_game *game)
{
	int	x;

	x = 0;
	while (x < WINDOW_W)
	{
		set_ray(&game->player, &game->ray, x);
		raycast(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}
