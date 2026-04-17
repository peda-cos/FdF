/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	compute_zoom(t_map *map)
{
	double	bbox_w;
	double	bbox_h;
	double	zoom_w;
	double	zoom_h;

	bbox_w = (map->width + map->height) * cos(0.523599);
	bbox_h = (map->width + map->height) * sin(0.523599)
		+ (double)(abs(map->z_max - map->z_min));
	zoom_w = WIN_WIDTH * 0.8 / bbox_w;
	zoom_h = WIN_HEIGHT * 0.8 / bbox_h;
	if (zoom_w < zoom_h)
	{
		if (zoom_w < 1.0)
			return (1.0);
		return (zoom_w);
	}
	if (zoom_h < 1.0)
		return (1.0);
	return (zoom_h);
}

void	init_camera(t_camera *cam, t_map *map)
{
	cam->projection = ISO;
	cam->z_scale = 1.0;
	cam->x_rot = 0;
	cam->y_rot = 0;
	cam->z_rot = 0;
	cam->zoom = compute_zoom(map);
	cam->offset_x = WIN_WIDTH / 2;
	cam->offset_y = WIN_HEIGHT / 2;
}

int	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (-1);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win)
		return (-1);
	fdf->img.ptr = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.ptr)
		return (-1);
	fdf->img.addr = mlx_get_data_addr(fdf->img.ptr, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	return (0);
}
