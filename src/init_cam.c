/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	init_cam(t_mlx *m)
{
	m->cam.x_ang = 60;
	m->cam.y_ang = 0;
	m->cam.z_ang = 45;
	m->cam.x_off = g_res_x / 2 + (g_res_x / 2) / 5;
	m->cam.y_off = g_res_y / 2;
	if (m->map->max < 100 && m->map->max != 0)
		m->cam.z_fac = (100.0 / m->map->max);
	else if (m->map->max > 200)
		m->cam.z_fac = (200.0 / m->map->max);
	else
		m->cam.z_fac = 1;
	m->cam.scl = 0.7;
	m->cam.scl_w = g_res_x / sqrt((double)m->map->w * (double)m->map->w
			+ (double)m->map->h * (double)m->map->h);
	m->cam.scl_h = m->cam.scl_w;
	if (m->map->w > 100 || m->map->h > 200)
		m->cam.line_type = 1;
	else
		m->cam.line_type = 0;
	m->cam.proj = PROJ_ISO;
	m->cam.arot_x = AUTO_STOP;
	m->cam.arot_y = AUTO_STOP;
	m->cam.arot_z = AUTO_STOP;
}
