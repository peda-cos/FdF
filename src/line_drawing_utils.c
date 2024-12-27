/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:37:33 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:37:45 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_diagonal_line(mlx_image_t *image, t_draw_parameters *draw_params,
		int start_color, int end_color)
{
	int	slope;

	if (draw_params->delta_x == 0)
		slope = 1;
	else
		slope = draw_params->delta_y / draw_params->delta_x;
	if (slope < 1)
		draw_shallow_line(draw_params, image, start_color, end_color);
	else
		draw_steep_line(draw_params, image, start_color, end_color);
}

void	draw_horizontal_line(mlx_image_t *image, t_map **map_data,
		t_draw_parameters *draw_params, t_position *pos)
{
	t_line_coordinates	coords;

	coords.start_x = map_data[pos->y][pos->x].x;
	coords.start_y = map_data[pos->y][pos->x].y;
	coords.end_x = map_data[pos->y][pos->x + 1].x;
	coords.end_y = map_data[pos->y][pos->x + 1].y;
	set_line_parameters(draw_params, &coords);
	draw_diagonal_line(image, draw_params, map_data[pos->y][pos->x].color,
		map_data[pos->y][pos->x + 1].color);
}

void	draw_vertical_line(mlx_image_t *image, t_map **map_data,
		t_draw_parameters *draw_params, t_position *pos)
{
	t_line_coordinates	coords;

	coords.start_x = map_data[pos->y][pos->x].x;
	coords.start_y = map_data[pos->y][pos->x].y;
	coords.end_x = map_data[pos->y + 1][pos->x].x;
	coords.end_y = map_data[pos->y + 1][pos->x].y;
	set_line_parameters(draw_params, &coords);
	draw_diagonal_line(image, draw_params, map_data[pos->y][pos->x].color,
		map_data[pos->y + 1][pos->x].color);
}
