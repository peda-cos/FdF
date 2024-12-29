/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:59:06 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/29 15:34:33 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_bresenham(t_point start, t_point end,
		t_bresenham *bresenham_state)
{
	if (start.x < end.x)
		bresenham_state->step_x = 1;
	else
		bresenham_state->step_x = -1;
	if (start.y < end.y)
		bresenham_state->step_y = 1;
	else
		bresenham_state->step_y = -1;
	bresenham_state->delta_x = abs(end.x - start.x);
	bresenham_state->delta_y = -abs(end.y - start.y);
	bresenham_state->error = bresenham_state->delta_x
		- bresenham_state->delta_y;
	bresenham_state->initial_x = start.x;
	bresenham_state->initial_y = start.y;
}

int	is_within_pixel_boundaries(t_point *point)
{
	if (point->x < 1 || point->x > WIDTH - 1)
		return (0);
	if (point->y < 1 || point->y > HEIGHT - 1)
		return (0);
	return (1);
}

void	clear_image_background(mlx_image_t *image)
{
	uint32_t	index;
	uint32_t	*pixels;

	pixels = (uint32_t *)image->pixels;
	index = 0;
	while (index < image->width * image->height)
	{
		pixels[index] = 0xFF000000;
		index++;
	}
}
