/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 00:55:51 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 00:55:52 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int abs_val(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

static unsigned int grad(t_point p, t_point s, t_point e)
{
	int total_len;

	total_len = calc_dist(s, e);
	return (calc_grad(p, s, total_len));
}

void bresenham_algorithm(mlx_image_t *img, t_point p1, t_point p2)
{
	int dx, sx, dy, sy, err, e2;
	t_point start, end, cur;

	start = p1;
	end = p2;
	dx = abs_val(end.x - start.x);
	sx = start.x < end.x ? 1 : -1;
	dy = -abs_val(end.y - start.y);
	sy = start.y < end.y ? 1 : -1;
	err = dx + dy;
	cur = start;
	while (1)
	{
		cur.c = grad(cur, start, end);
		if (cur.x >= 0 && cur.x < g_res_x && cur.y >= 0 && cur.y < g_res_y)
			mlx_put_pixel(img, cur.x, cur.y, cur.c);
		if (cur.x == end.x && cur.y == end.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			if (cur.x == end.x)
				break;
			err += dy;
			cur.x += sx;
		}
		if (e2 <= dx)
		{
			if (cur.y == end.y)
				break;
			err += dx;
			cur.y += sy;
		}
	}
}
