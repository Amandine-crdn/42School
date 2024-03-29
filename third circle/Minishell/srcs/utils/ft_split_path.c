/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerdan <acerdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by acerdan           #+#    #+#             */
/*   Updated: 2022/07/26 07:51:15 by acerdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_charset(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static size_t	count_charset(char *s, char c)
{
	int		count;
	size_t	words;

	count = 1;
	words = 0;
	while (s && *s)
	{
		if (is_charset(*s, c))
			count = 1;
		else if (count == 1)
		{
			words++;
			count = 0;
		}
		s++;
	}
	return (words);
}

static size_t	count_char(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_charset(s[i], c))
		i++;
	return (i);
}

static char	**ft_free(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

char	**ft_split_path(char *s, char c)
{
	char	**new;
	size_t	count;
	size_t	j;
	size_t	k;

	j = -1;
	count = count_charset(s, c);
	k = 0;
	new = (char **)malloc(sizeof(char *) * (count + 1));
	if (!s || !new)
		return (NULL);
	while (++j < count)
	{
		while (is_charset(*s, c))
			s++;
		new[j] = (char *)malloc(sizeof(char) * (count_char(s, c) + 1));
		if (!new[j])
			return (ft_free(new));
		k = 0;
		while (*s && !is_charset(*s, c))
			new[j][k++] = *s++;
		new[j][k] = 0;
	}
	new[j] = 0;
	return (new);
}
