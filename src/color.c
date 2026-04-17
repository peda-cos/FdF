/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	lerp_channel(int a, int b, double t)
{
	return ((int)(a + (b - a) * t));
}

int	interpolate_color(int c1, int c2, double t)
{
	int	r;
	int	g;
	int	b;

	if (c1 == c2)
		return (c1);
	r = lerp_channel((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, t);
	g = lerp_channel((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, t);
	b = lerp_channel(c1 & 0xFF, c2 & 0xFF, t);
	return (r << 16 | g << 8 | b);
}

void	assign_default_colors(t_map *map)
{
	int		x;
	int		y;
	double	t;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->colors[y][x] == 0)
			{
				if (map->z_min == map->z_max)
					t = 0.0;
				else
					t = (double)(map->z_values[y][x] - map->z_min)
						/ (map->z_max - map->z_min);
				map->colors[y][x] = interpolate_color(0x0000FF, 0xFF0000, t);
			}
			x++;
		}
		y++;
	}
}

double	line_progress(int current, int start, int end)
{
	if (start == end)
		return (0.0);
	return ((double)(current - start) / (double)(end - start));
}
