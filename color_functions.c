/* ************************************************************************** */

/*                                                                            */

/*                                                        :::      ::::::::   */

/*   color_functions.c                                  :+:      :+:    :+:   */

/*                                                    +:+ +:+        
	+:+     */

/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+      
	+#+        */

/*                                                +#+#+#+#+#+  
	+#+            */

/*   Created: 2024/11/15 20:20:24 by peda-cos          #+#    #+#              */

/*   Updated: 2024/12/17 00:40:00 by peda-cos         ###   ########.fr        */

/*                                                                            */

/* ************************************************************************** */

#include "fdf.h"

void	set_point_color(t_point *point, t_map map)

{

	t_color col;

	int delta_value;



	delta_value = map.max - point->value;

	col.r = calculate_interpolation((g_red >> 24) & 0xFF, (g_blue >> 24) & 0xFF,
			delta_value, map.range);

	col.g = calculate_interpolation((g_red >> 16) & 0xFF, (g_blue >> 16) & 0xFF,
			delta_value, map.range);

	col.b = calculate_interpolation((g_red >> 8) & 0xFF, (g_blue >> 8) & 0xFF,
			delta_value, map.range);

	col.a = calculate_interpolation(g_red & 0xFF, g_blue & 0xFF, delta_value,
			map.range);

	point->color = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.a;

}



unsigned int	calculate_gradient(t_point point1, t_point point2,
		int total_length)

{

	t_color col;

	unsigned int color;

	int current_length;



	current_length = calculate_distance(point1, point2);

	col.r = calculate_interpolation((point2.color >> 24) & 0xFF,
			(point1.color >> 24) & 0xFF, current_length, total_length);

	col.g = calculate_interpolation((point2.color >> 16) & 0xFF,
			(point1.color >> 16) & 0xFF, current_length, total_length);

	col.b = calculate_interpolation((point2.color >> 8) & 0xFF,
			(point1.color >> 8) & 0xFF, current_length, total_length);

	col.a = calculate_interpolation(point2.color & 0xFF, point1.color & 0xFF,
			current_length, total_length);

	color = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.a;

	return (color);

}



void	fill_background(t_mlx *mlx_instance, unsigned int color)

{

	uint32_t y;

	uint32_t x;



	y = 0;

	while (y < (uint32_t)g_resolution_y)

	{

		x = 0;

		while (x < (uint32_t)g_resolution_x)

		{

			mlx_put_pixel(mlx_instance->img, x, y, color);

			x++;

		}

		y++;

	}

}

