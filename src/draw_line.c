/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)(img->addr + offset) = color;
}

static t_line	init_bresenham(int x0, int y0, int x1, int y1)
{
	t_line	l;

	l.x0 = x0;
	l.y0 = y0;
	l.x1 = x1;
	l.y1 = y1;
	l.dx = abs(x1 - x0);
	l.dy = abs(y1 - y0);
	l.sx = 1;
	if (x0 > x1)
		l.sx = -1;
	l.sy = 1;
	if (y0 > y1)
		l.sy = -1;
	l.err = l.dx - l.dy;
	return (l);
}

static void	step_bresenham(t_line *l)
{
	int	e2;

	e2 = 2 * l->err;
	if (e2 > -l->dy)
	{
		l->err -= l->dy;
		l->x0 += l->sx;
	}
	if (e2 < l->dx)
	{
		l->err += l->dx;
		l->y0 += l->sy;
	}
}

static void	draw_bresenham(t_img *img, t_point p0, t_point p1, t_line *l)
{
	int	steps;
	int	step;

	steps = l->dx;
	if (l->dy > l->dx)
		steps = l->dy;
	if (steps == 0)
	{
		put_pixel(img, l->x0, l->y0, p0.color);
		return ;
	}
	step = 0;
	while (1)
	{
		put_pixel(img, l->x0, l->y0,
			interpolate_color(p0.color, p1.color,
				line_progress(step, 0, steps)));
		if (l->x0 == l->x1 && l->y0 == l->y1)
			break ;
		step_bresenham(l);
		step++;
	}
}

void	draw_line(t_img *img, t_point p0, t_point p1)
{
	t_line	l;

	l = init_bresenham((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y);
	draw_bresenham(img, p0, p1, &l);
}
