/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:55:56 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/29 15:34:11 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_camera(t_fdf *fdf)
{
	fdf->camera = ft_calloc(1, sizeof(t_camera));
	fdf->camera->projection_type = ISOMETRIC;
	fdf->camera->zoom_level = fminf((WIDTH / fdf->map->width), (HEIGHT
				/ fdf->map->height)) / 2;
	fdf->camera->z_scale_factor = 1;
	fdf->camera->x_offset = 0;
	fdf->camera->y_offset = 0;
}

void	reset_camera(t_fdf *fdf)
{
	fdf->camera->zoom_level = fminf((WIDTH / fdf->map->width), (HEIGHT
				/ fdf->map->height)) / 2;
	fdf->camera->z_scale_factor = 1;
	fdf->camera->x_offset = 0;
	fdf->camera->y_offset = 0;
}

t_point	project_point(t_point point, t_fdf *fdf)
{
	int	transformed_x;
	int	transformed_y;

	transformed_x = point.x;
	transformed_y = point.y;
	point.x = point.x * fdf->camera->zoom_level - ((fdf->map->width
				* fdf->camera->zoom_level) / 2);
	point.y = point.y * fdf->camera->zoom_level - ((fdf->map->height
				* fdf->camera->zoom_level) / 2);
	point.z = point.z * fdf->camera->zoom_level / fdf->camera->z_scale_factor;
	if (fdf->camera->projection_type == ISOMETRIC)
	{
		transformed_x = (point.x - point.y) * cos(M_PI / 6);
		transformed_y = (-point.z + (point.x + point.y) * sin(M_PI / 6));
	}
	point.x = transformed_x + WIDTH / 2 + fdf->camera->x_offset;
	point.y = transformed_y + HEIGHT / 2 + fdf->camera->y_offset;
	return (point);
}
