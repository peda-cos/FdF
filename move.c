/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+            */
/*   Created: 2024/11/15 20:23:06 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/16 22:45:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	move_map(t_mlx *mlx_instance, t_direction direction)
{
	int dx;
	int dy;
	int h;
	int w;

	dx = 0;
	dy = 0;
	if (direction == UP)
		dy = -g_move_amount;
	else if (direction == DOWN)
		dy = g_move_amount;
	else if (direction == LEFT)
		dx = -g_move_amount;
	else if (direction == RIGHT)
		dx = g_move_amount;
	h = 0;
	while (h < mlx_instance->map->height)
	{
		w = 0;
		while (w < mlx_instance->map->width)
		{
			mlx_instance->map->grid[h][w].x += dx;
			mlx_instance->map->grid[h][w].y += dy;
			w++;
		}
		h++;
	}
	draw_grid(mlx_instance, mlx_instance->map);
}
