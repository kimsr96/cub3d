/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:42:18 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 13:59:35 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	word_len(char const *s, char *charset)
{
	int	i;

	i = 0;
	while (!check_charset(s[i], charset) && s[i])
		i++;
	return (i);
}

static int	word_count(char const *s, char *charset)
{
	size_t	i;
	size_t	j;
	int		cnt;

	j = 0;
	cnt = 0;
	while (s[j] && check_charset(s[j], charset))
		j++;
	i = j;
	while (s[i])
	{
		if (check_charset(s[i], charset))
		{
			while (s[i] && check_charset(s[i], charset))
				i++;
			if (s[i] == '\0')
				break ;
			cnt += 1;
		}
		else
			i++;
	}
	if (i == 0 || i == j)
		return (cnt);
	return (cnt + 1);
}

static char	*put_word(char const *s, int len)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split2(char *s, char *charset)
{
	int		i;
	int		idx;
	char	**ret;

	i = -1;
	idx = 0;
	if (!s)
		return (NULL);
	ret = (char **)ft_calloc(word_count(s, charset) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (s[++i])
	{
		if (!check_charset(s[i], charset))
		{
			ret[idx] = put_word(&s[i], word_len(&s[i], charset));
			if (!ret[idx++])
				return (ft_freeall(ret));
			i += (word_len(&s[i], charset) - 1);
		}
	}
	ret[idx] = NULL;
	return (ret);
}
