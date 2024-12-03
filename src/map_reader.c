/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:03:51 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:47:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	set_map_dimensions(char *file_path, t_fdf *fdf)
{
	int16_t		fd;
	char		current_char;
	char		previous_char;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		clean_exit(file_path, fdf);
	previous_char = ' ';
	while (read(fd, &current_char, 1))
	{
		if (!ft_isspace(current_char) && ft_isspace(previous_char))
			fdf->vertex_count++;
		if (current_char == '\n')
			fdf->map_height++;
		if (current_char == '\n' && !fdf->map_width)
			fdf->map_width = fdf->vertex_count;
		previous_char = current_char;
	}
	if (current_char != '\n')
		fdf->map_height++;
	if (!fdf->map_width)
		fdf->map_width = fdf->vertex_count;
	close(fd);
	if (!fdf->vertex_count || fdf->map_width * fdf->map_height != fdf->vertex_count)
		clean_exit("Invalid map", fdf);
}

static int32_t	read_next_value(int fd, t_fdf *fdf)
{
	int		bytes_read;
	int		index;
	char	value_buffer[64];

	bytes_read = 1;
	index = 0;
	while (bytes_read && index < 63)
	{
		bytes_read = read(fd, &value_buffer[index], 1);
		if (bytes_read == -1)
		{
			close(fd);
			clean_exit("File read failed", fdf);
		}
		if (index && ft_isspace(value_buffer[index]))
			break ;
		if (!ft_isspace(value_buffer[index]) && bytes_read)
			index++;
	}
	value_buffer[index] = '\0';
	validate_value(value_buffer, fdf);
	return (ft_atoi(value_buffer));
}

static void	parse_map_data(char *file_path, t_fdf *fdf)
{
	int		fd;
	size_t	vertex_index;
	size_t	x_position;
	size_t	y_position;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		clean_exit(file_path, fdf);
	vertex_index = 0;
	x_position = 0;
	y_position = 0;
	while (vertex_index < fdf->vertex_count)
	{
		fdf->vertices[vertex_index].x = x_position;
		fdf->vertices[vertex_index].y = y_position;
		fdf->vertices[vertex_index].z = read_next_value(fd, fdf);
		vertex_index++;
		x_position++;
		if (x_position == fdf->map_width)
		{
			y_position++;
			x_position = 0;
		}
	}
	close(fd);
}

void	initialize_fdf(char *file_path, t_fdf *fdf)
{
	set_map_dimensions(file_path, fdf);
	fdf->vertices = (t_vertex *)malloc(fdf->vertex_count * sizeof(t_vertex));
	if (!fdf->vertices)
		clean_exit("Memory allocation error", fdf);
	parse_map_data(file_path, fdf);
	set_vertex_colors(fdf);
	fdf->height_scale = 1;
}