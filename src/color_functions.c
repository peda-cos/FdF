/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	set_pt_clr(t_point *p, t_map mp)
{
	unsigned int	clr;
	int				d_val;
	int				r;
	int				g;
	int				b;
	int				a;

	d_val = mp.max - p->value;
	r = calc_ip((g_c2 >> 24) & 0xFF, (g_c1 >> 24) & 0xFF, d_val, mp.range);
	g = calc_ip((g_c2 >> 16) & 0xFF, (g_c1 >> 16) & 0xFF, d_val, mp.range);
	b = calc_ip((g_c2 >> 8) & 0xFF, (g_c1 >> 8) & 0xFF, d_val, mp.range);
	a = calc_ip(g_c2 & 0xFF, g_c1 & 0xFF, d_val, mp.range);
	clr = (r << 24) | (g << 16) | (b << 8) | a;
	p->c = clr;
}

unsigned int	calc_grad(t_point p1, t_point p2, int tl)
{
	unsigned int	clr;
	int				l;
	int				r;
	int				g;
	int				b;
	int				a;

	l = calc_dist(p1, p2);
	r = calc_ip((p2.c >> 24) & 0xFF, (p1.c >> 24) & 0xFF, l, tl);
	g = calc_ip((p2.c >> 16) & 0xFF, (p1.c >> 16) & 0xFF, l, tl);
	b = calc_ip((p2.c >> 8) & 0xFF, (p1.c >> 8) & 0xFF, l, tl);
	a = calc_ip(p2.c & 0xFF, p1.c & 0xFF, l, tl);
	clr = (r << 24) | (g << 16) | (b << 8) | a;
	return (clr);
}

void	fill_bg(t_mlx *m, unsigned int clr)
{
	uint32_t	y;
	uint32_t	x;

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
