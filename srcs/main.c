/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:28:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/24 18:21:27 by seungryk         ###   ########.fr       */
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
	//asset_init(&g);
	read_map(&g, argv[1]);
	//mlx_put_window(&g);
	return (0);
}
