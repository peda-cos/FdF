/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

static void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)(img->addr + offset) = color;
}

static t_line	init_bresenham(t_point p0, t_point p1)
{
	t_line	line;

	line.dx = abs((int)p1.x - (int)p0.x);
	line.dy = abs((int)p1.y - (int)p0.y);
	line.sx = 1;
	if (p0.x > p1.x)
		line.sx = -1;
	line.sy = 1;
	if (p0.y > p1.y)
		line.sy = -1;
	line.err = line.dx - line.dy;
	return (line);
}

static void	step_bresenham(t_line *line, t_point *p0)
{
	int	e2;

	e2 = 2 * line->err;
	if (e2 > -line->dy)
	{
		line->err -= line->dy;
		p0->x += line->sx;
	}
	if (e2 < line->dx)
	{
		line->err += line->dx;
		p0->y += line->sy;
	}
}

void	draw_line(t_img *img, t_point p0, t_point p1)
{
	t_line	line;
	int		steps;
	int		step;
	int		color;

	line = init_bresenham(p0, p1);
	steps = line.dx;
	if (line.dy > line.dx)
		steps = line.dy;
	step = 0;
	while (1)
	{
		color = interpolate_color(p0.color, p1.color,
				line_progress(step, 0, steps));
		put_pixel(img, (int)p0.x, (int)p0.y, color);
		if ((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y)
			break ;
		step_bresenham(&line, &p0);
		step++;
	}
}
