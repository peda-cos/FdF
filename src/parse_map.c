/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**read_lines(int fd, int *count)
{
	char	**lines;
	char	*line;

	lines = malloc(sizeof(char *) * 4096);
	if (!lines)
		return (NULL);
	*count = 0;
	line = get_next_line(fd);
	while (line && *count < 4096)
	{
		lines[*count] = line;
		(*count)++;
		line = get_next_line(fd);
	}
	return (lines);
}

static int	alloc_map_rows(t_map *map, char *first_line)
{
	char	**first;
	int		i;

	first = ft_split(first_line, ' ');
	if (!first)
		return (-1);
	map->width = 0;
	while (first[map->width])
		map->width++;
	free_split(first);
	map->z_values = malloc(sizeof(int *) * map->height);
	map->colors = malloc(sizeof(int *) * map->height);
	if (!map->z_values || !map->colors)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		map->z_values[i] = malloc(sizeof(int) * map->width);
		map->colors[i] = malloc(sizeof(int) * map->width);
		if (!map->z_values[i] || !map->colors[i])
			return (-1);
		i++;
	}
	return (0);
}

static int	parse_line(char *line, t_map *map, int row)
{
	char	**tokens;
	int		col;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (-1);
	col = 0;
	while (col < map->width && tokens[col])
	{
		parse_token(tokens[col], &map->z_values[row][col],
			&map->colors[row][col]);
		if (map->z_values[row][col] < map->z_min)
			map->z_min = map->z_values[row][col];
		if (map->z_values[row][col] > map->z_max)
			map->z_max = map->z_values[row][col];
		col++;
	}
	free_split(tokens);
	return (0);
}

static void	process_lines(char **lines, t_map *map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		parse_line(lines[i], map, i);
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	parse_map(char *filename, t_map *map)
{
	char	**lines;
	int		count;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = read_lines(fd, &count);
	close(fd);
	if (!lines || count == 0)
		return (-1);
	map->height = count;
	map->z_min = 0;
	map->z_max = 0;
	if (alloc_map_rows(map, lines[0]) < 0)
		return (-1);
	process_lines(lines, map, count);
	return (0);
}
