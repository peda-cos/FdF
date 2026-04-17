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

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->z_values[i]);
		i++;
	}
	free(map->z_values);
	map->z_values = NULL;
	i = 0;
	while (i < map->height)
	{
		free(map->colors[i]);
		i++;
	}
	free(map->colors);
	map->colors = NULL;
}

void	cleanup_fdf(t_fdf *fdf)
{
	if (fdf->img.ptr)
		mlx_destroy_image(fdf->mlx, fdf->img.ptr);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	free_map(&fdf->map);
}

int	close_handler(t_fdf *fdf)
{
	cleanup_fdf(fdf);
	exit(0);
	return (0);
}
