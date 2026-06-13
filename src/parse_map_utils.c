/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX_LINES 4096

static char	**alloc_lines(int *count)
{
	char	**lines;

	lines = malloc(sizeof(char *) * MAX_LINES);
	if (!lines)
		return (NULL);
	*count = 0;
	return (lines);
}

static int	read_loop(int fd, char **lines, int *count)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	while (line)
	{
		if (*count >= MAX_LINES)
		{
			free(line);
			return (-1);
		}
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (len > 1 && line[len - 2] == '\r')
			line[len - 2] = '\0';
		lines[*count] = line;
		(*count)++;
		line = get_next_line(fd);
	}
	if (*count == 0)
		return (-1);
	return (0);
}

char	**read_lines(int fd, int *count)
{
	char	**lines;

	lines = alloc_lines(count);
	if (!lines)
		return (NULL);
	if (read_loop(fd, lines, count) < 0)
	{
		free_lines(lines, *count);
		free(lines);
		return (NULL);
	}
	return (lines);
}

int	get_width(char *first_line)
{
	char	**first;
	int		width;

	first = ft_split(first_line, ' ');
	if (!first)
		return (-1);
	width = 0;
	while (first[width])
		width++;
	free_split(first);
	return (width);
}

int	check_dim(int width, int height)
{
	if (width <= 0 || width > MAX_LINES || height <= 0
		|| height > MAX_LINES)
		return (-1);
	return (0);
}
