/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map_partial(t_map *map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map->z_values[i]);
		free(map->colors[i]);
		i++;
	}
	free(map->z_values);
	free(map->colors);
}

void	free_map(t_map *map)
{
	free_map_partial(map, map->height);
	map->z_values = NULL;
	map->colors = NULL;
}

void	cleanup_fdf(t_fdf *fdf)
{
	int	i;

	if (fdf->img.ptr)
		mlx_destroy_image(fdf->mlx, fdf->img.ptr);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	if (fdf->projected)
	{
		i = 0;
		while (i < fdf->map.height)
		{
			free(fdf->projected[i]);
			i++;
		}
		free(fdf->projected);
	}
	free_map(&fdf->map);
}

int	close_handler(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	cleanup_fdf(fdf);
	exit(0);
}
