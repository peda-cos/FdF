/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:35 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/28 21:37:11 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*initialize_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->total_points = 0;
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	map->points = NULL;
	return (map);
}

void	free_map(t_map *map)
{
	free(map->points);
	free(map);
}

int	count_columns(char *line, char delimiter)
{
	int	i;
	int	column_count;

	i = 0;
	column_count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == delimiter)
		{
			while (line[i] && (line[i] == delimiter || line[i] == '\n'))
				i++;
		}
		else
		{
			while (line[i] && line[i] != delimiter)
				i++;
			column_count++;
		}
	}
	return (column_count);
}

int	validate_file_extension(char *file)
{
	int	file_descriptor;

	if (!ft_strnstr(file, ".fdf", ft_strlen(file)))
		exit_with_error(ERROR_FILE_EXTENSION);
	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor == -1)
		exit_with_error(ERROR_FILE_OPEN);
	return (file_descriptor);
}
