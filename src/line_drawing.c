/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:36:44 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:36:58 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_shallow_line(t_draw_parameters *draw_params, mlx_image_t *image,
		int start_color, int end_color)
{
	float	current_x;
	float	current_y;
	int		pixel_idx;

	current_x = draw_params->current_x;
	current_y = draw_params->current_y;
	if (current_x > 0 && current_x < image->width && current_y > 0
		&& current_y < image->height)
		mlx_put_pixel(image, current_x, current_y,
			get_color_gradient(start_color, end_color, 0,
				draw_params->delta_x));
	pixel_idx = 0;
	while (pixel_idx < draw_params->delta_x)
	{
		current_x += draw_params->step_x;
		if (draw_params->decision <= 0)
			draw_params->decision += 2 * draw_params->delta_y;
		else
		{
			current_y += draw_params->step_y;
			draw_params->decision += (2 * draw_params->delta_y) - (2
					* draw_params->delta_x);
		}
		if (current_x > 0 && current_x < image->width && current_y > 0
			&& current_y < image->height)
			mlx_put_pixel(image, current_x, current_y,
				get_color_gradient(start_color, end_color, pixel_idx + 1,
					draw_params->delta_x));
		pixel_idx++;
	}
}

void	draw_steep_line(t_draw_parameters *draw_params, mlx_image_t *image,
		int start_color, int end_color)
{
	float	current_x;
	float	current_y;
	int		pixel_idx;

	current_x = draw_params->current_x;
	current_y = draw_params->current_y;
	if (current_x > 0 && current_x < image->width && current_y > 0
		&& current_y < image->height)
		mlx_put_pixel(image, current_x, current_y,
			get_color_gradient(start_color, end_color, 0,
				draw_params->delta_y));
	pixel_idx = 0;
	while (pixel_idx < draw_params->delta_y)
	{
		current_y += draw_params->step_y;
		if (draw_params->decision <= 0)
			draw_params->decision += 2 * draw_params->delta_x;
		else
		{
			current_x += draw_params->step_x;
			draw_params->decision += (2 * draw_params->delta_x) - (2
					* draw_params->delta_y);
		}
		if (current_x > 0 && current_x < image->width && current_y > 0
			&& current_y < image->height)
			mlx_put_pixel(image, current_x, current_y,
				get_color_gradient(start_color, end_color, pixel_idx + 1,
					draw_params->delta_y));
		pixel_idx++;
	}
}

void	draw_map(mlx_image_t *image, t_map **map_data,
		t_map_dimensions *map_dims)
{
	t_draw_parameters	draw_params;
	t_position			pos;

	pos.y = 0;
	while (pos.y < map_dims->height)
	{
		pos.x = 0;
		while (pos.x < map_dims->width)
		{
			if (pos.x < map_dims->width - 1)
				draw_horizontal_line(image, map_data, &draw_params, &pos);
			if (pos.y < map_dims->height - 1)
				draw_vertical_line(image, map_data, &draw_params, &pos);
			pos.x++;
		}
		pos.y++;
	}
}
