/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:22:26 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/14 14:53:18 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	terminate(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	//free;
	exit(0);
	return (1);
}

int	handle_keypress(int	keycode, t_game *game)
{
	if (keycode == 53)
		terminate(game)	;
	if (keycode == 13 | keycode == 0 | keycode == 1 | keycode == 2)
		move_player(keycode, game);
	if (keycode == 123 | keycode == 124)
		rotate_player(keycode, game);
	draw(game);
	return (0);
}
