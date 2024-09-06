/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:07:31 by hyeonble          #+#    #+#             */
/*   Updated: 2024/09/06 17:12:13 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_image(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_W || y >= WINDOW_H)
		return ;
	dst = image->addr + (y * image->l) + (x * image->bpp / 8);
	*(unsigned int *)dst = color;
}

void	fill_black(t_image *image)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_W)
	{
		j = 0;
		while (j < WINDOW_H)
		{
			put_pixel_to_image(image, i, j, COLOR_BLACK);
			j++;
		}
		i++;
	}
}
