/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+
	+#+         */
/*                                                +#+#+#+#+#+
	+#+            */
/*   Created: 2024/11/15 20:24:20 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:15:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int	validate_filename(const char *filename)
{
	size_t len;

	len = ft_strlen(filename);
	return (len > 4 && ft_strncmp(filename + len - 4, ".fdf", 4) == 0);
}

static int	get_map_dimensions(int fd, t_map *map)
{
	char *line;
	char **split_line;
	int width;

	map->width = -1;
	map->height = 0;
	while ((line = get_next_line(fd)))
	{
		width = 0;
		map->height++;
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
			return (0);
		while (split_line[width])
			width++;
		free_str_array(split_line);
		if (map->width != -1 && width != map->width)
			return (0);
		map->width = width;
	}
	return (1);
}

static int	parse_map_line(int fd, t_map *map)
{
	int i;
	int j;
	char *line;
	char **split_line;

	i = 0;
	while ((line = get_next_line(fd)))
	{
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
			return (0);
		j = 0;
		while (j < map->width)
		{
			map->grid[i][j].value = ft_atoi(split_line[j]);
			j++;
		}
		free_str_array(split_line);
		i++;
	}
	return (1);
}

static void	find_min_max(t_map *map)
{
	int h;
	int w;

	map->max = map->grid[0][0].value;
	map->min = map->grid[0][0].value;
	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if (map->grid[h][w].value > map->max)
				map->max = map->grid[h][w].value;
			if (map->grid[h][w].value < map->min)
				map->min = map->grid[h][w].value;
			w++;
		}
		h++;
	}
	map->range = (long)map->max - (long)map->min;
}

int	parse_map(char *filename, t_map *map)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1 || !get_map_dimensions(fd, map) || map->width == -1
		|| !validate_filename(filename) || map->width > 5000
		|| map->height > 5000 || !allocate_map(map))
	{
		close_safe(&fd);
		return (0);
	}
	close_safe(&fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (safe_exit_on_error(NULL, map, fd, 0));
	if (!parse_map_line(fd, map))
		return (safe_exit_on_error(NULL, map, fd, 0));
	close_safe(&fd);
	find_min_max(map);
	return (1);
}
