/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+      
	+#+         */
/*                                                +#+#+#+#+#+  
	+#+            */
/*   Created: 2024/11/15 20:24:28 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:30:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static void	update_zoom(t_map *map, t_screen *screen, int factor)
{
	int h;
	int w;

	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			map->grid[h][w].x += factor * (w - h) * screen->half_tile_width;
			map->grid[h][w].y += factor * ((w + h) * screen->half_tile_height)
				- map->grid[h][w].value * screen->half_tile_height / 2;
			w++;
		}
		h++;
	}
}

void	zoom_increase(t_mlx *mlx_instance)
{
	t_map *map;

	map = mlx_instance->map;
	mlx_instance->screen.half_tile_width *= 2;
	mlx_instance->screen.half_tile_height *= 2;
	update_zoom(map, &mlx_instance->screen, 1);
	draw_grid(mlx_instance, map);
}

void	zoom_decrease(t_mlx *mlx_instance)
{
	t_map *map;

	map = mlx_instance->map;
	if (mlx_instance->screen.half_tile_width / 2 < 2)
		return ;
	mlx_instance->screen.half_tile_width /= 2;
	mlx_instance->screen.half_tile_height /= 2;
	update_zoom(map, &mlx_instance->screen, -1);
	draw_grid(mlx_instance, map);
}
