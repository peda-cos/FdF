/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:38:48 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:39:02 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rescale_map(t_map **map_data, t_map_dimensions *map_dims)
{
	t_map_offset	offset;
	unsigned int	y_idx;
	unsigned int	x_idx;

	set_map_offset(&offset, map_dims);
	y_idx = 0;
	while (y_idx < map_dims->height)
	{
		x_idx = 0;
		while (x_idx < map_dims->width)
		{
			zoom_map(map_data, &offset, x_idx, y_idx);
			x_idx++;
		}
		y_idx++;
	}
}

void	zoom_map(t_map **map_data, t_map_offset *offset, unsigned int x_idx,
		unsigned int y_idx)
{
	int	new_x;
	int	new_y;

	new_x = map_data[y_idx][x_idx].x * offset->scaling_interval;
	new_y = map_data[y_idx][x_idx].y * offset->scaling_interval;
	map_data[y_idx][x_idx].x = get_x_derivative(new_x, new_y,
			map_data[y_idx][x_idx].z) + offset->start_x;
	map_data[y_idx][x_idx].y = get_y_derivative(new_x, new_y,
			map_data[y_idx][x_idx].z) + offset->start_y;
}

float	get_x_derivative(float x_val, float y_val, int z_val)
{
	float	der_x;

	der_x = cos(45 * (PI / 180)) * x_val - sin(45 * (PI / 180)) * y_val;
	x_val = der_x - z_val * cos(60 * (PI / 180));
	return (x_val);
}

float	get_y_derivative(float x_val, float y_val, int z_val)
{
	float	der_y;

	der_y = sin(45 * (PI / 180)) * x_val + cos(45 * (PI / 180)) * y_val;
	y_val = der_y - z_val * sin(60 * (PI / 180));
	return (y_val);
}
