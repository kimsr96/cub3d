/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:45:49 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/25 15:58:48 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valid_identifier(char *line, int idx)
{
	int			i;
	const char	*id[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	const char	*name;

	i = -1;
	name = id[idx];
	while (line[++i])
	{
		if (line[i] == ' ')
			continue ;
		if (!ft_strncmp(name, &line[i], 2))
			i++;
	}
}

void	is_valid_wall_texture(t_game *g)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (i < 4)
			g->asset.walls[i] = path2img(g->mlx, g->asset.split_line[i][1]);
		i++;
	}
	g->asset.floor = g->asset.split_line[4][1];
	g->asset.ceiling = g->asset.split_line[5][1];
}

int	get_parsing_line(t_game *g, char *line)
{
	int			i;
	int			len;
	const char	*id[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	while (i < 6)
	{
		if (i < 4)
			len = 2;
		else
			len = 1;
		if (ft_strnstr(line, id[i], ft_strlen(line)))
		{
			if (g->asset.split_line[i])
				error_msg();
			g->asset.split_line[i] = ft_split2(line, "\x20\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	get_map_info(t_game *g, int fd)
{	
	int		idx;
	char	*line;
	char	**map;

	idx = 0;
	map = malloc(sizeof(char *) * g->map.total_line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > 1)
			map[idx++] = ft_strdup(line);
		free(line);
	}
	map[idx] = NULL;
	g->map.info = map;
}

void	get_identifier(t_game *g, int fd)
{
	int		i;
	int		num;
	char	*line;

	i = 0;
	num = 0;
	g->asset.split_line = malloc(sizeof(char **) * 6);
	if (!g->asset.split_line)
		exit(1);
	ft_memset(g->asset.split_line, 0, sizeof(char **) * 6);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg();
		if (ft_strlen(line) && num < 6)
			num += get_parsing_line(g, ft_strdup(line));
		free(line);
		if (num == 6)
			break ;
	}
	if (num != 6)
		error_msg();
}

void	print_identifier(t_game *g)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		printf("path: %s\n", g->asset.split_line[i][1]);
		i++;
	}
}

void	print_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map.info[i])
	{
		printf("%s", g->map.info[i]);
		i++;
	}
}

void	get_info(t_game *g, char *f_name)
{
	int		fd;

	fd = open(f_name, O_RDONLY);
	if (fd < 0)
		error_msg();
	get_identifier(g, fd);
	get_map_info(g, fd);
	//print_identifier(g);
	//print_map(g);
	close(fd);
	is_valid_wall_texture(g);
}
