/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:32:03 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/30 21:57:31 by hyeonble         ###   ########.fr       */
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
	// print_map(g);
	// print_player(g);
	//check_map(g);
}
