/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:17 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/29 23:39:06 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	load_map(char *file, t_map *map)
{
	unsigned int	columns;
	char			*line;
	int				file_descriptor;

	file_descriptor = validate_file_extension(file);
	line = get_next_line(file_descriptor);
	while (line)
	{
		columns = count_columns(line, ' ');
		free(line);
		if (map->height == 0)
			map->width = columns;
		if (map->width != columns)
			exit_with_error(ERROR_MAP_WIDTH);
		map->height++;
		line = get_next_line(file_descriptor);
	}
	free(line);
	close(file_descriptor);
	map->total_points = map->height * map->width;
	if (map->total_points == 0)
		exit_with_error(ERROR_MAP_EMPTY);
	map->points = ft_calloc(map->total_points, sizeof(t_point));
	fill_map(file, map);
}

void	fill_map(char *file, t_map *map)
{
	unsigned int	line_index;
	int				file_descriptor;
	char			*line;

	line_index = 0;
	file_descriptor = open(file, O_RDONLY);
	line = get_next_line(file_descriptor);
	while (line)
	{
		parse_line_into_points(line, map, line_index);
		free(line);
		line = get_next_line(file_descriptor);
		if (!line)
			break ;
		line_index++;
	}
	free(line);
	close(file_descriptor);
}

void	parse_line_into_points(char *line, t_map *map, int line_index)
{
	char	**columns;
	int		column_index;
	int		start_index;

	column_index = 0;
	start_index = line_index * map->width;
	columns = ft_split(line, ' ');
	while (columns[column_index] && columns[column_index][0] != '\n')
	{
		map->points[start_index + column_index].x = column_index;
		map->points[start_index + column_index].y = line_index;
		map->points[start_index
			+ column_index].z = ft_atoi(columns[column_index]);
		if (map->points[start_index + column_index].z > map->max_z)
			map->max_z = map->points[start_index + column_index].z;
		if (map->points[start_index + column_index].z < map->min_z)
			map->min_z = map->points[start_index + column_index].z;
		map->points[start_index
			+ column_index].color = parse_color(columns[column_index]);
		column_index++;
	}
	free_string_array(columns);
}
