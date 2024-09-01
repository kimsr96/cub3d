/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:28:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/30 21:57:26 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		error_msg();
	ft_memset(&g, 0, sizeof(g));
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WINDOW_W, WINDOW_H, "cub3d");
	//asset_init(&g);
	read_map(&g, argv[1]);
	//mlx_put_window(&g);
	// mlx_loop_hook(g.mlx, draw, &g);
	draw(&g);
	mlx_loop(g.mlx);
	return (0);
}