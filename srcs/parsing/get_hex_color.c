/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hex_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:01:26 by seungryk          #+#    #+#             */
/*   Updated: 2024/09/29 21:51:20 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valid_color_format(char **color_2d)
{
	int	i;
	int	j;

	i = 0;
	if (!color_2d)
		error_msg();
	while (color_2d[i])
	{
		j = 0;
		while (color_2d[i][j])
		{
			if (!ft_isdigit(color_2d[i][j]))
				error_msg();
			j++;
		}
		i++;
	}
	if (i != 3)
		error_msg();
}

int	combine_color(char **color_2d)
{
	int	i;
	int	rgb[3];
	int	color;

	i = 0;
	valid_color_format(color_2d);
	while (i < 3)
	{
		rgb[i] = ft_atoi(color_2d[i]);
		if (rgb[i] > 255 || rgb[i] < 0)
			error_msg();
		i++;
	}
	color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (color);
}
