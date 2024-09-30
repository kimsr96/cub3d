/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:28:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/09/29 20:29:57 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_image *img, void *mlx)
{
	img->img = mlx_new_image(mlx, WINDOW_W, WINDOW_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l, &img->endian);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		error_msg();
	ft_memset(&g, 0, sizeof(g));
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WINDOW_W, WINDOW_H, "cub3d");
	init_image(&g.image, g.mlx);
	read_map(&g, argv[1]);
	init_player(&g.map, &g.player);
	init_ray(&g.map, &g.ray);
	draw(&g);
	mlx_hook(g.win, KEYPRESS, 0, handle_keypress, &g);
	mlx_hook(g.win, DESTROYNOTIFY, 0, terminate, &g);
	mlx_loop(g.mlx);
	return (0);
}
