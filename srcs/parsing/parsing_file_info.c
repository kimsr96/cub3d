/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:45:49 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/27 19:48:32 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	insert_info(t_game *g, char ***split_line)
{
	int		i;
	char	**color_2d;

	i = 0;
	while (i < 6)
	{
		if (i < 4)
			g->asset.wall_texture[i] = path2img(g->mlx, split_line[i][1]);
		else if (i == 4)
		{
			color_2d = ft_split(split_line[4][1], ',');
			g->asset.floor_color = combine_color(color_2d);
		}
		else if (i == 5)
		{
			color_2d = ft_split(split_line[5][1], ',');
			g->asset.ceiling_color = combine_color(color_2d);
		}
		i++;
	}
}

void	count_comma(char *s)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == ',')
			cnt++;
		i++;
	}
	if (cnt != 2)
		error_msg();
}

int	get_parsing_line(char ***split_line, char *line)
{
	int			i;
	const char	*id[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	while (i < 6)
	{
		if (ft_strnstr(line, id[i], ft_strlen(line)))
		{
			if (split_line[i])
				error_msg();
			split_line[i] = ft_split2(line, "\x20\n");
			if (i >= 4)
				count_comma(split_line[i][1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	get_texture(t_game *g, char ***split_line, int fd, int *map_start)
{
	int		i;
	int		num;
	char	*line;

	i = 0;
	num = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			error_msg();
		(*map_start)++;
		if (ft_strlen(line) && num < 6)
			num += get_parsing_line(split_line, ft_strdup(line));
		free(line);
		if (num == 6)
			break ;
	}
	if (num != 6)
		error_msg();
	insert_info(g, split_line);
}

void	get_info(t_game *g, char *f_name)
{
	int		fd;
	int		map_start;
	char	***split_line;

	map_start = 0;
	split_line = malloc(sizeof(char **) * 6);
	if (!split_line)
		exit(1);
	ft_memset(split_line, 0, sizeof(char **) * 6);
	fd = open(f_name, O_RDONLY);
	if (fd < 0)
		error_msg();
	get_texture(g, split_line, fd, &map_start);
	get_map_info(g, fd, &map_start);
	close(fd);
	get_map(g, f_name, map_start);
}
