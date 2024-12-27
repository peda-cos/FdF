/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:34:47 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:35:06 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_and_draw_map(mlx_image_t *image, char *file_path)
{
	t_map_dimensions	map_dims;
	char				**map_lines;
	t_map				**map_data;
	size_t				line_count;

	line_count = get_file_line_count(file_path);
	if (line_count == 0)
		return (1);
	map_lines = read_file_lines(file_path, line_count);
	if (map_lines == NULL)
		return (1);
	map_data = parse_map_data(map_lines, line_count, &map_dims);
	if (map_data == NULL)
	{
		free_string_array(map_lines, line_count);
		return (1);
	}
	rescale_map(map_data, &map_dims);
	draw_map(image, map_data, &map_dims);
	free_string_array(map_lines, line_count);
	free_map_data(map_data, line_count);
	return (0);
}

int	handle_map(mlx_t *mlx_ptr, mlx_image_t *image, char *file_path)
{
	int	result;

	result = read_and_draw_map(image, file_path);
	if (result == 1)
	{
		perror("Failed to open or parse the file.");
		mlx_delete_image(mlx_ptr, image);
		mlx_terminate(mlx_ptr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
