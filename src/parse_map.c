/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:35:15 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:35:35 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_file_line_count(char *file_path)
{
	char	*one_line;
	int		fd;
	size_t	count;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (0);
	one_line = get_next_line(fd);
	if (!one_line)
	{
		close(fd);
		return (0);
	}
	while (one_line != NULL)
	{
		count++;
		free(one_line);
		one_line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**read_file_lines(char *file_path, size_t line_count)
{
	char	**lines;
	char	*one_line;
	int		fd;
	size_t	i;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lines = (char **)malloc(line_count * sizeof(char *));
	if (!lines)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		one_line = get_next_line(fd);
		lines[i] = one_line;
		i++;
	}
	close(fd);
	return (lines);
}

t_map	**parse_map_data(char **map_lines, size_t height,
		t_map_dimensions *map_dims)
{
	t_map			**map_data;
	unsigned int	y;

	map_data = (t_map **)malloc(height * sizeof(t_map *));
	if (!map_data)
		return (NULL);
	y = 0;
	while (y < height)
	{
		if (!process_map_row(map_data, map_dims, map_lines, y))
			return (NULL);
		y++;
	}
	return (map_data);
}

void	free_string_array(char **ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_map_data(t_map **map_data, size_t height)
{
	size_t	y;

	y = 0;
	while (y < height)
	{
		free(map_data[y]);
		y++;
	}
	free(map_data);
}
