/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:23:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/09/06 17:43:55 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pass_line_before_map(char *f_name, int map_start)
{
	int		fd;
	char	*line;

	fd = open(f_name, O_RDONLY);
	if (fd < 0)
		exit (1);
	while (--map_start)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	return (fd);
}

void	*xpmpath_to_img(void *mlx, char *path)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	printf("path: %s\n", path);
	if (!img)
		error_msg();
	return (img);
}

void	error_msg(void)
{
	ft_putstr_fd("Error\n", 2);
	exit (1);
}
