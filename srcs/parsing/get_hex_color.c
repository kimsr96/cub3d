/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hex_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:01:26 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/25 16:54:43 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*int_to_hex(int num)
{
	const char	*hex = "0123456789ABCDEF";
	char		*ret;

	ret = malloc(sizeof(char) * 3);
	if (!ret)
		exit (1);
	ret[0] = hex[num / 16];
	ret[1] = hex[num % 16];
	ret[2] = '\0';
	return (ret);
}

char    *int_to_hex_color(char **color_2d)
{
	int     i;
	int     color_num;
	char	*temp;
	char	*hex_color;

	i = 0;
	temp = NULL;
	hex_color = ft_calloc(11, sizeof(char));
	ft_strlcat(hex_color, "0x00", 11);
	while (color_2d[i])
	{
		color_num = ft_atoi(color_2d[i]);
		printf("color_num : %d\n", color_num);
		if (color_num < 0 || color_num > 255)
			error_msg();
		temp = int_to_hex(color_num);
		ft_strlcat(hex_color, temp, 11);
		free(temp);
		i++;
	}
	return (hex_color);
}
