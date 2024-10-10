/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:41:40 by hyeonble          #+#    #+#             */
/*   Updated: 2024/10/10 19:39:44 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

double	get_wall_x(t_game *game, int side)
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

int	get_tex_x(t_game *game, double wall_x, int side)
{
	int	tex_x;

	tex_x = (int)(wall_x * 64);
	if (side == WALL_X && game->ray.raydir_x < 0)
		tex_x = 64 - tex_x - 1;
	if (side == WALL_Y && game->ray.raydir_y > 0)
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

unsigned int	get_tex_color(t_game *game, int tex_x, int tex_y)
{
	int		texnum;
	t_image	*texture;
	char	*texture_data;
	char	*tex_ptr;

	texnum = game->draw.texnum;
	texture = &game->asset.texture[texnum];
	texture_data = texture->addr;
	tex_ptr = texture_data + (tex_y * texture->l + tex_x * (texture->bpp / 8));
	return (*(unsigned int *)tex_ptr);
}

int	select_texture(t_game *game, int side)
{
	if (side == WALL_X)
	{
		if (game->ray.raydir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (game->ray.raydir_y > 0)
			return (0);
		else
			return (1);
	}
}
