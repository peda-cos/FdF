/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

void	handle_translate(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Left)
		fdf->cam.offset_x -= 20;
	if (keycode == XK_Right)
		fdf->cam.offset_x += 20;
	if (keycode == XK_Up)
		fdf->cam.offset_y -= 20;
	if (keycode == XK_Down)
		fdf->cam.offset_y += 20;
}

void	handle_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == XK_n)
		fdf->cam.zoom *= 1.1;
	if (keycode == XK_m && fdf->cam.zoom > 0.1)
		fdf->cam.zoom *= 0.9;
}

void	handle_z_scale(int keycode, t_fdf *fdf)
{
	if (keycode == XK_j)
		fdf->cam.z_scale -= 0.1;
	if (keycode == XK_k)
		fdf->cam.z_scale += 0.1;
}

void	handle_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == XK_w)
		fdf->cam.x_rot -= 0.05;
	if (keycode == XK_s)
		fdf->cam.x_rot += 0.05;
	if (keycode == XK_a)
		fdf->cam.z_rot -= 0.05;
	if (keycode == XK_d)
		fdf->cam.z_rot += 0.05;
	if (keycode == XK_q)
		fdf->cam.y_rot -= 0.05;
	if (keycode == XK_e)
		fdf->cam.y_rot += 0.05;
	if (keycode == XK_p && fdf->cam.projection == ISO)
		fdf->cam.projection = PARALLEL;
	else if (keycode == XK_p)
		fdf->cam.projection = ISO;
	if (keycode == XK_r)
		init_camera(&fdf->cam, &fdf->map);
}
