/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fc_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:04:27 by seungryk          #+#    #+#             */
/*   Updated: 2024/09/29 21:51:53 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	len_without_space(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

char	*remove_space(char *s, int idx)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	i = 0;
	len = len_without_space(&s[idx]);
	//if (len == (int)ft_strlen(&s[idx]))
	//	return (s);
	ret = malloc(sizeof(char) * (len + idx));
	ret[len + idx - 1] = '\0';
	i = 0;
	j = 0;
	while (s[i] && ret[j])
	{
		if (i < idx)
			ret[j++] = s[i];
		else if (s[i] != ' ' && s[i] != '\n')
			ret[j++] = s[i];
		i++;
	}
	return (ret);
}
