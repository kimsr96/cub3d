/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:23:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/09/30 13:19:50 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pass_empty_line(int fd, int *map_start)
{
	int		i;
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg();
		(*map_start)++;
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\n')
				break ;
			i++;
		}
		if (line[i] != '\0')
			break ;
		free(line);
	}
	free(line);
}

void	get_map_info(t_game *g, int fd, int *map_start)
{	
	int		idx;
	int		col;
	char	*line;

	idx = 0;
	col = 0;
	pass_empty_line(fd, map_start);
	g->map.row = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		g->map.row++;
		if ((int)ft_strlen(line) > col)
			col = (int)ft_strlen(line);
		free(line);
	}
	g->map.col = col - 1;
}

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
		free(line);
	}
	return (fd);
}

void	*xpmpath_to_img(void *mlx, char *path)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
		error_msg();
	return (img);
}

void	error_msg(void)
{
	ft_putstr_fd("Error\n", 2);
	exit (1);
}
