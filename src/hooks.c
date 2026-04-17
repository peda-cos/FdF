/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

static void	handle_move(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Left)
		fdf->cam.offset_x -= 20;
	if (keycode == XK_Right)
		fdf->cam.offset_x += 20;
	if (keycode == XK_Up)
		fdf->cam.offset_y -= 20;
	if (keycode == XK_Down)
		fdf->cam.offset_y += 20;
	if (keycode == XK_n)
		fdf->cam.zoom *= 1.1;
	if (keycode == XK_m && fdf->cam.zoom > 0.1)
		fdf->cam.zoom *= 0.9;
	if (keycode == XK_j)
		fdf->cam.z_scale -= 0.1;
	if (keycode == XK_k)
		fdf->cam.z_scale += 0.1;
}

static void	handle_rotate(int keycode, t_fdf *fdf)
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

static int	key_handler(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		close_handler(fdf);
	handle_move(keycode, fdf);
	handle_rotate(keycode, fdf);
	render(fdf);
	return (0);
}

static int	mouse_handler(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
		fdf->cam.zoom *= 1.1;
	if (button == 5 && fdf->cam.zoom > 0.1)
		fdf->cam.zoom *= 0.9;
	render(fdf);
	return (0);
}

void	setup_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, (int (*)())(void *)key_handler, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, (int (*)())(void *)mouse_handler, fdf);
	mlx_hook(fdf->win, 17, 0L, (int (*)())(void *)close_handler, fdf);
}
