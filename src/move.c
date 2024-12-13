/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:23:06 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 01:25:02 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	move(t_mlx *mlx, t_dir dir)
{
	int	h;
	int	w;
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (dir == UP)
		dy = 1;
	if (dir == DOWN)
		dy = -1;
	if (dir == LEFT)
		dx = 1;
	if (dir == RIGHT)
		dx = -1;
	h = 0;
	while (h < mlx->map->h)
	{
		w = 0;
		while (w < mlx->map->w)
		{
			mlx->map->grid[h][w].x += dx * g_mv_amt;
			mlx->map->grid[h][w].y += dy * g_mv_amt;
			w++;
		}
		h++;
	}
}
