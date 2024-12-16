/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+      
	+#+         */
/*                                                +#+#+#+#+#+  
	+#+            */
/*   Created: 2024/11/15 20:20:59 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:30:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static void	calculate_screen(t_map *map, t_screen *screen)
{
	screen->half_tile_width = (g_resolution_x > g_resolution_y) ? g_resolution_y
		/ (map->width + map->height) : g_resolution_x / (map->width
			+ map->height);
	screen->half_tile_width = (screen->half_tile_width < 2) ? 2 : screen->half_tile_width;
	screen->half_tile_height = screen->half_tile_width * tan(M_PI / 6);
	screen->start_x = map->height * screen->half_tile_width;
	screen->margin_x = (g_resolution_x - map->width * screen->half_tile_width)
		/ 2;
	screen->margin_y = (g_resolution_y - map->height * screen->half_tile_height)
		/ 2;
}

static void	calculate_coordinates(t_map *map, t_screen *screen)
{
	int h;
	int w;
	int height_modifier;
	t_point *point;

	h = 0;
	height_modifier = screen->half_tile_height / 2;
	if (height_modifier < 1)
		height_modifier = 1;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			point = &map->grid[h][w];
			point->x = screen->start_x + (w - h) * screen->half_tile_width;
			point->y = screen->margin_y + (w + h) * screen->half_tile_height
				- point->value * height_modifier;
			set_point_color(point, *map);
			w++;
		}
		h++;
	}
}

void	run_fdf(t_mlx *mlx_instance, t_map *map)
{
	calculate_screen(map, &mlx_instance->screen);
	calculate_coordinates(map, &mlx_instance->screen);
	draw_grid(mlx_instance, map);
}

void	skip_lines(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close_safe(&fd);
}
