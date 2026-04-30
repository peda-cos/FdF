/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	alloc_cols(t_map *map, int i)
{
	map->z_values[i] = malloc(sizeof(int) * map->width);
	map->colors[i] = malloc(sizeof(int) * map->width);
	if (!map->z_values[i] || !map->colors[i])
	{
		free_map_partial(map, i);
		return (-1);
	}
	return (0);
}

int	alloc_map_rows(t_map *map, char *first_line)
{
	int		i;

	map->width = get_width(first_line);
	if (map->width < 0)
		return (-1);
	if (check_dim(map->width, map->height) < 0)
		return (-1);
	map->z_values = malloc(sizeof(int *) * map->height);
	map->colors = malloc(sizeof(int *) * map->height);
	if (!map->z_values || !map->colors)
	{
		free(map->z_values);
		free(map->colors);
		return (-1);
	}
	i = 0;
	while (i < map->height)
	{
		if (alloc_cols(map, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	process_lines(char **lines, t_map *map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (parse_line(lines[i], map, i) < 0)
		{
			while (i < count)
			{
				free(lines[i]);
				i++;
			}
			free(lines);
			return (-1);
		}
		free(lines[i]);
		i++;
	}
	free(lines);
	return (0);
}
