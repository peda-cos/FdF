/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:24:28 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:24:31 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void zoom_inc(t_mlx *m)
{
	int     h;
	int     w;
	t_map   *mp;

	mp = m->map;
	h = 0;
	while (h < mp->h)
	{
		w = 0;
		while (w < mp->w)
		{
			mp->grid[h][w].x += (w - h) * m->s.half_tile_w;
			mp->grid[h][w].y += (w + h) * (m->s.half_tile_h)
				- mp->grid[h][w].value * m->s.half_tile_h / 2;
			w++;
		}
		h++;
	}
	m->s.half_tile_w *= 2;
	m->s.half_tile_h *= 2;
	draw_grid(m, mp);
}

void zoom_dec(t_mlx *m)
{
	int     h;
	int     w;
	t_map   *mp;

	mp = m->map;
	if (m->s.half_tile_w / 2 <= 3)
		return ;
	m->s.half_tile_w /= 2;
	m->s.half_tile_h /= 2;
	h = 0;
	while (h < mp->h)
	{
		w = 0;
		while (w < mp->w)
		{
			mp->grid[h][w].x -= (w - h) * m->s.half_tile_w;
			mp->grid[h][w].y -= (w + h) * (m->s.half_tile_h)
				- mp->grid[h][w].value * m->s.half_tile_h / 2;
			w++;
		}
		h++;
	}
	draw_grid(m, mp);
}
