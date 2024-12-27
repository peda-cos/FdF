/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:36:01 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:36:27 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map_element(t_map *map_element, char *value, unsigned int x_idx,
		unsigned int y_idx)
{
	char	**z_color;

	z_color = NULL;
	if (ft_strchr(value, ',') != NULL)
	{
		z_color = ft_split(value, ',');
		if (!z_color)
			return ;
		map_element->z = ft_atoi(z_color[0]);
		map_element->color = parse_hex_string(z_color[1]);
		free_string_array(z_color, get_string_array_width(z_color));
	}
	else
	{
		map_element->z = ft_atoi(value);
		map_element->color = parse_hex_string("0x8A2BE2");
		set_default_color(&map_element->color, map_element->z);
	}
	map_element->x = x_idx;
	map_element->y = y_idx;
}

bool	check_map_columns(char **values, t_map_dimensions *map_dims,
		unsigned int current_row)
{
	size_t	column_count;

	if (current_row == 0)
		map_dims->width = get_string_array_width(values);
	column_count = get_string_array_width(values);
	if (column_count != map_dims->width)
	{
		perror("Wrong format of the map: inconsistent columns.");
		free_string_array(values, column_count);
		return (false);
	}
	return (true);
}

bool	allocate_and_fill_map_row(char **values, t_map **map_data,
		unsigned int current_row, t_map_dimensions *map_dims)
{
	t_map	*row_ptr;
	size_t	x_idx;

	row_ptr = (t_map *)malloc(map_dims->width * sizeof(t_map));
	if (!row_ptr)
		return (false);
	x_idx = 0;
	while (x_idx < map_dims->width)
	{
		fill_map_element(&row_ptr[x_idx], values[x_idx], x_idx, current_row);
		x_idx++;
	}
	map_data[current_row] = row_ptr;
	return (true);
}

bool	process_map_row(t_map **map_data, t_map_dimensions *map_dims,
		char **map_lines, unsigned int current_row)
{
	char	**values;

	values = ft_split(map_lines[current_row], ' ');
	if (!values)
	{
		free_map_data(map_data, current_row);
		return (false);
	}
	if (!check_map_columns(values, map_dims, current_row)
		|| !allocate_and_fill_map_row(values, map_data, current_row, map_dims))
	{
		free_string_array(map_lines, map_dims->height);
		free_map_data(map_data, current_row);
		return (false);
	}
	free_string_array(values, map_dims->width);
	return (true);
}

size_t	get_string_array_width(char **values)
{
	size_t	count;

	count = 0;
	if (!values)
		return (0);
	while (values[count])
		count++;
	return (count);
}
