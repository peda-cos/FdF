/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###  ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	apply_projection(double px, double py, double pz, t_fdf *fdf)
{
	t_point	result;

	ft_bzero(&result, sizeof(t_point));
	if (fdf->cam.projection == ISO)
	{
		result.x = (px - py) * cos(ISO_ANGLE);
		result.y = (px + py) * sin(ISO_ANGLE) - pz;
	}
	else
	{
		result.x = px;
		result.y = py - pz;
	}
	result.x *= fdf->cam.zoom;
	result.y *= fdf->cam.zoom;
	result.x += fdf->cam.offset_x;
	result.y += fdf->cam.offset_y;
	return (result);
}

t_point	project_point_trig(int x, int y, t_fdf *fdf, t_trig *trig)
{
	double	px;
	double	py;
	double	pz;
	t_point	result;

	px = x - fdf->map.width / 2.0;
	py = y - fdf->map.height / 2.0;
	pz = fdf->map.z_values[y][x] * fdf->cam.z_scale;
	rotate_x(&py, &pz, trig->sin_x, trig->cos_x);
	rotate_y(&px, &pz, trig->sin_y, trig->cos_y);
	rotate_z(&px, &py, trig->sin_z, trig->cos_z);
	result = apply_projection(px, py, pz, fdf);
	result.color = fdf->map.colors[y][x];
	return (result);
}

t_point	project_point(int x, int y, t_fdf *fdf)
{
	t_trig	trig;

	trig.sin_x = sin(fdf->cam.x_rot);
	trig.cos_x = cos(fdf->cam.x_rot);
	trig.sin_y = sin(fdf->cam.y_rot);
	trig.cos_y = cos(fdf->cam.y_rot);
	trig.sin_z = sin(fdf->cam.z_rot);
	trig.cos_z = cos(fdf->cam.z_rot);
	return (project_point_trig(x, y, fdf, &trig));
}
