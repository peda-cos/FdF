/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	build_projection_cache(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf->trig.sin_x = sin(fdf->cam.x_rot);
	fdf->trig.cos_x = cos(fdf->cam.x_rot);
	fdf->trig.sin_y = sin(fdf->cam.y_rot);
	fdf->trig.cos_y = cos(fdf->cam.y_rot);
	fdf->trig.sin_z = sin(fdf->cam.z_rot);
	fdf->trig.cos_z = cos(fdf->cam.z_rot);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->projected[y][x] = project_point_trig(x, y, fdf, &fdf->trig);
			x++;
		}
		y++;
	}
}

static void	draw_links(t_fdf *fdf, int x, int y)
{
	t_point	cur;
	t_point	right;
	t_point	bot;

	cur = fdf->projected[y][x];
	if (x + 1 < fdf->map.width)
	{
		right = fdf->projected[y][x + 1];
		draw_line(&fdf->img, cur, right);
	}
	if (y + 1 < fdf->map.height)
	{
		bot = fdf->projected[y + 1][x];
		draw_line(&fdf->img, cur, bot);
	}
}

static void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			draw_links(fdf, x, y);
			x++;
		}
		y++;
	}
}

void	render(t_fdf *fdf)
{
	ft_bzero(fdf->img.addr, WIN_HEIGHT * fdf->img.line_len);
	build_projection_cache(fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.ptr, 0, 0);
	fdf->dirty = 0;
}

int	render_loop(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->dirty)
		render(fdf);
	return (0);
}
