/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+            */
/*   Created: 2024/11/15 20:22:29 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:30:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	cleanup_exit(t_mlx *mlx_instance, int exit_code)
{
	if (mlx_instance->mlx)
		mlx_terminate(mlx_instance->mlx);
	if (mlx_instance->map)
		free_grid(mlx_instance->map, 0);
	exit(exit_code);
}

int	allocate_map(t_map *map)
{
	int i;

	map->grid = malloc(map->height * sizeof(t_point *));
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(map->width * sizeof(t_point));
		if (!map->grid[i])
			return (safe_exit_on_error(NULL, map->grid, -1, 0));
		i++;
	}
	return (1);
}

int	free_grid(t_map *map, int return_code)
{
	int i;

	i = 0;
	if (map->grid)
	{
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			map->grid[i] = NULL;
			i++;
		}
		free(map->grid);
	}
	free(map);
	return (return_code);
}

int	free_str_array(char **array)
{
	size_t i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	return (-1);
}

int	free_and_return(void *pointer, int return_code)
{
	if (pointer)
		free(pointer);
	return (return_code);
}
