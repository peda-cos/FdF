/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:22:29 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	cleanup_exit(t_mlx *m, int r)
{
	mlx_terminate(m->mlx);
	free_grid(m->map, 0);
	exit(r);
}

int	alloc_map(t_map *mp)
{
	int	i;

	mp->grid = malloc((mp->h) * (sizeof(t_point *)));
	if (!mp->grid)
		return (0);
	i = 0;
	while (i < mp->h)
	{
		mp->grid[i] = malloc((mp->w) * (sizeof(t_point)));
		if (!mp->grid[i])
			return (free_grid(mp, 0));
		i++;
	}
	return (1);
}

int	free_grid(t_map *mp, int r)
{
	int	i;

	i = 0;
	if (mp->grid)
	{
		while (i < mp->h)
		{
			if (mp->grid[i])
				free(mp->grid[i]);
			mp->grid[i] = NULL;
			i++;
		}
		free(mp->grid);
	}
	free(mp);
	mp = NULL;
	return (r);
}

int	free_strarr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
	return (-1);
}

int	free_ret(void *p, int r)
{
	free(p);
	return (r);
}
