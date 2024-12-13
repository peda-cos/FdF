/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:23:06 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:23:07 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void shift_map(t_mlx *m, t_dir d)
{
	int h;
	int w;
	int dx;
	int dy;

	dx = 0;
	dy = 0;
	if (d == UP)
		dy = 1;
	if (d == DOWN)
		dy = -1;
	if (d == LEFT)
		dx = 1;
	if (d == RIGHT)
		dx = -1;
	h = 0;
	while (h < m->map->h)
	{
		w = 0;
		while (w < m->map->w)
		{
			m->map->grid[h][w].x += dx * g_mv_amt;
			m->map->grid[h][w].y += dy * g_mv_amt;
			w++;
		}
		h++;
	}
}
