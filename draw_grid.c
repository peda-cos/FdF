/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+
	+#+            */
/*   Created: 2024/12/16 23:30:00 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:40:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_grid(t_mlx *mlx_instance, t_map *map)
{
	int	h;
	int	w;

	fill_background(mlx_instance, g_bg_color);
	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if (w + 1 < map->width)
				draw_line(mlx_instance->img, map->grid[h][w], map->grid[h][w
					+ 1]);
			if (h + 1 < map->height)
				draw_line(mlx_instance->img, map->grid[h][w], map->grid[h
					+ 1][w]);
			w++;
		}
		h++;
	}
}
