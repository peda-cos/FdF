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

static void	draw_links(t_fdf *fdf, int x, int y)
{
	t_point	cur;
	t_point	right;
	t_point	bot;

	cur = project_point(x, y, fdf);
	if (x + 1 < fdf->map.width)
	{
		right = project_point(x + 1, y, fdf);
		draw_line(&fdf->img, cur, right);
	}
	if (y + 1 < fdf->map.height)
	{
		bot = project_point(x, y + 1, fdf);
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
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.ptr, 0, 0);
}
