/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:59:40 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/28 21:37:25 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_map(t_fdf *fdf)
{
	unsigned int	i;
	unsigned int	map_width;
	t_point			current_point;
	t_point			*points;

	clear_image_background(fdf->image);
	i = -1;
	points = fdf->map->points;
	map_width = fdf->map->width;
	while (++i < fdf->map->total_points)
	{
		current_point = project_point(fdf->map->points[i], fdf);
		if (i % map_width != fdf->map->width - 1)
			draw_line(current_point, project_point(points[i + 1], fdf),
				fdf->image);
		if (i + map_width < fdf->map->total_points)
			draw_line(current_point, project_point(points[i + map_width], fdf),
				fdf->image);
	}
	mlx_image_to_window(fdf->mlx_instance, fdf->image, 0, 0);
}

void	draw_line(t_point start, t_point end, mlx_image_t *image)
{
	t_bresenham	bresenham_state;

	initialize_bresenham(start, end, &bresenham_state);
	while (1)
	{
		if (start.x == end.x && start.y == end.y)
			return ;
		if (is_within_pixel_boundaries(&start))
			mlx_put_pixel(image, start.x, start.y, interpolate_color(start, end,
					bresenham_state));
		if (2 * bresenham_state.error >= bresenham_state.delta_y)
		{
			if (start.x == end.x)
				return ;
			bresenham_state.error += bresenham_state.delta_y;
			start.x += bresenham_state.step_x;
		}
		if (2 * bresenham_state.error <= bresenham_state.delta_x)
		{
			if (start.y == end.y)
				return ;
			bresenham_state.error += bresenham_state.delta_x;
			start.y += bresenham_state.step_y;
		}
	}
}
