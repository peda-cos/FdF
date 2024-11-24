/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:46:10 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/24 14:46:10 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	first_pass(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (map->width == 0)
			map->width = count_words(line, ' ');
		map->height++;
		free(line);
	}
}

void	second_pass(int fd, t_map *map, int y)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		map->points[y] = parse_line(line, y);
		y++;
		free(line);
	}
}

t_map	*parse_map(const char *filename)
{
	int		fd;
	t_map	*map;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening file");
	map = initialize_map();
	first_pass(fd, map);
	close(fd);
	map->points = (t_point **)safe_malloc(sizeof(t_point *) * map->height);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error reopening file");
	y = 0;
	second_pass(fd, map, y);
	close(fd);
	return (map);
}
