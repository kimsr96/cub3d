/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:32:03 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/24 18:30:10 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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

static void	count_line(t_game *g, char *f_name)
{
	char	*line;
	int		fd;

	fd = open(f_name, O_RDONLY);
	if (fd < 0)
		error_msg();
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		g->map.total_line++;
	}
	close(fd);
}

void	read_map(t_game *g, char *f_name)
{
	check_type(f_name);
	count_line(g, f_name);
    get_info(g, f_name);
	//check_map(g);
}
