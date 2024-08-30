/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:32:03 by seungryk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/30 21:28:57 by hyeonble         ###   ########.fr       */
=======
/*   Updated: 2024/08/30 21:46:10 by seungryk         ###   ########.fr       */
>>>>>>> cb6e89df58a13aa7089f785e18dfde3f0c84963a
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_type(char *file_name)
{
	int		i;
	size_t	len;

	i = 0;
	while (file_name[i])
	{
		if (file_name[i + 1] == '.' && file_name[i] != '/')
		{
			len = ft_strlen(&file_name[i + 1]);
			if (!ft_memcmp(&file_name[i + 1], ".cub", len))
				return ;
		}
		i++;
	}
	error_msg();
}

void	read_map(t_game *g, char *f_name)
{
	check_type(f_name);
    get_info(g, f_name);
	valid_map(g);
<<<<<<< HEAD
	// print_map(g);
	// print_player(g);
=======
	//print_map(g);
	print_player(g);
>>>>>>> cb6e89df58a13aa7089f785e18dfde3f0c84963a
	//check_map(g);
}
