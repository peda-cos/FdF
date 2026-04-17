/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(double *y, double *z, double angle)
{
	double	prev;

	prev = *y;
	*y = prev * cos(angle) - *z * sin(angle);
	*z = prev * sin(angle) + *z * cos(angle);
}

static void	rotate_y(double *x, double *z, double angle)
{
	double	prev;

	prev = *x;
	*x = prev * cos(angle) - *z * sin(angle);
	*z = prev * sin(angle) + *z * cos(angle);
}

static void	rotate_z(double *x, double *y, double angle)
{
	double	prev;

	prev = *x;
	*x = prev * cos(angle) - *y * sin(angle);
	*y = prev * sin(angle) + *y * cos(angle);
}

static t_point	apply_projection(double px, double py, double pz, t_fdf *fdf)
{
	t_point	result;

	ft_bzero(&result, sizeof(t_point));
	if (fdf->cam.projection == ISO)
	{
		result.x = (px - py) * cos(0.523599);
		result.y = (px + py) * sin(0.523599) - pz;
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

t_point	project_point(int x, int y, t_fdf *fdf)
{
	double	px;
	double	py;
	double	pz;
	t_point	result;

	px = x - fdf->map.width / 2.0;
	py = y - fdf->map.height / 2.0;
	pz = fdf->map.z_values[y][x] * fdf->cam.z_scale;
	rotate_x(&py, &pz, fdf->cam.x_rot);
	rotate_y(&px, &pz, fdf->cam.y_rot);
	rotate_z(&px, &py, fdf->cam.z_rot);
	result = apply_projection(px, py, pz, fdf);
	result.color = fdf->map.colors[y][x];
	return (result);
}
