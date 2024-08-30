/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:22:33 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/30 21:39:21 by seungryk         ###   ########.fr       */
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
	}
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

int	is_empty_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	insert_to_2darr(int fd, t_game *g)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	while (y < g->map.row)
	{
		line = get_next_line(fd);
		if (!line || is_empty_line(line))
			break ;
		x = 0;
		while (line[x] && line[x] != '\n')
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

void	pass_left_line(int fd)
{
	int		i;
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\n')
				error_msg();
			i++;
		}
	}
}

void	get_map(t_game *g, char *f_name, int map_start)
{
	int	fd;
	int	i;

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
	pass_left_line(fd);
	close(fd);
}
