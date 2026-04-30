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

static int	key_handler(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keycode == XK_Escape)
		close_handler(fdf);
	handle_translate(keycode, fdf);
	handle_zoom(keycode, fdf);
	handle_z_scale(keycode, fdf);
	handle_rotate(keycode, fdf);
	fdf->dirty = 1;
	return (0);
}

static int	mouse_handler(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	fdf = param;
	if (button == 4)
		fdf->cam.zoom *= 1.1;
	if (button == 5 && fdf->cam.zoom > 0.1)
		fdf->cam.zoom *= 0.9;
	fdf->dirty = 1;
	return (0);
}

void	setup_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, (int (*)())key_handler, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, (int (*)())mouse_handler, fdf);
	mlx_hook(fdf->win, 17, 0L, (int (*)())close_handler, fdf);
	mlx_loop_hook(fdf->mlx, (int (*)())render_loop, fdf);
}
