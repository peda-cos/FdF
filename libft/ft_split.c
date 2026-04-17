/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_all(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
}

static char	*get_word(char const *s, char c, size_t *pos)
{
	size_t	start;
	size_t	len;

	while (s[*pos] == c)
		(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != c)
		(*pos)++;
	len = *pos - start;
	return (ft_substr(s, start, len));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	nwords;
	size_t	i;
	size_t	pos;

	if (!s)
		return (NULL);
	nwords = count_words(s, c);
	arr = (char **)malloc((nwords + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < nwords)
	{
		arr[i] = get_word(s, c, &pos);
		if (!arr[i])
		{
			free_all(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
