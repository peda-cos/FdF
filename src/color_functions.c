/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:20:24 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:20:27 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void    set_pt_clr(t_point *p, t_map mp)
{
	unsigned int    clr;
	t_color         col;
	int             d_val;

	d_val = mp.max - p->value;
	col.r = calc_ip((g_c2 >> 24) & 0xFF, (g_c1 >> 24) & 0xFF, d_val, mp.range);
	col.g = calc_ip((g_c2 >> 16) & 0xFF, (g_c1 >> 16) & 0xFF, d_val, mp.range);
	col.b = calc_ip((g_c2 >> 8) & 0xFF, (g_c1 >> 8) & 0xFF, d_val, mp.range);
	col.a = calc_ip(g_c2 & 0xFF, g_c1 & 0xFF, d_val, mp.range);
	clr = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.a;
	p->c = clr;
}

unsigned int    calc_grad(t_point p1, t_point p2, int tl)
{
	unsigned int    clr;
	t_color         col;
	int             l;

	l = calc_dist(p1, p2);
	col.r = calc_ip((p2.c >> 24) & 0xFF, (p1.c >> 24) & 0xFF, l, tl);
	col.g = calc_ip((p2.c >> 16) & 0xFF, (p1.c >> 16) & 0xFF, l, tl);
	col.b = calc_ip((p2.c >> 8) & 0xFF, (p1.c >> 8) & 0xFF, l, tl);
	col.a = calc_ip(p2.c & 0xFF, p1.c & 0xFF, l, tl);
	clr = (col.r << 24) | (col.g << 16) | (col.b << 8) | col.a;
	return (clr);
}

void    fill_bg(t_mlx *m, unsigned int clr)
{
	uint32_t y;
	uint32_t x;

	y = 0;
	while (y < (uint32_t)g_res_y)
	{
		x = 0;
		while (x < (uint32_t)g_res_x)
		{
			mlx_put_pixel(m->img1, x, y, clr);
			x++;
		}
		y++;
	}
}
