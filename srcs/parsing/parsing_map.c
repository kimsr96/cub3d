/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:22:33 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/27 15:22:21 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	pass_empty_line(int fd, int *map_start)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
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
	}
}

void	get_map_info(t_game *g, int fd, int *map_start)
{	
	int		idx;
	char	*line;
	size_t	col;

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
		if (ft_strlen(line) > col)
			col = ft_strlen(line);
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
	}
	return (fd);
}

void	insert_to_2darr(int fd, t_game *g)
{
	size_t	x;
	size_t	y;
	char	*line;

	y = 0;
	while (y < g->map.row)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		x = 0;
		while (line[x] && line[x] != '\n' && g->map.map_2d[y][x])
		{
			g->map.map_2d[y][x] = line[x];
			x++;
		}
		while (x < g->map.col)
		{
			g->map.map_2d[y][x] = ' ';
			x++;
		}
		y++;
	}
}

void	get_map(t_game *g, char *f_name, int map_start)
{
	int		fd;
	size_t	i;

	i = 0;
	fd = pass_line_before_map(f_name, map_start);
	g->map.map_2d = malloc(sizeof(char *) * (g->map.row + 1));
	if (!g->map.map_2d)
		exit (1);
	g->map.map_2d[g->map.row] = NULL;
	while (i < g->map.row)
	{
		g->map.map_2d[i] = malloc(sizeof(char) * g->map.col + 1);
		if (!g->map.map_2d[i])
			exit (1);
		g->map.map_2d[i][g->map.col] = '\0';
		i++;
	}
	insert_to_2darr(fd, g);
}
