/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:24:20 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	name_check(char *file)
{
	if (ft_strlen(file) < 4)
		return (0);
	file += ft_strlen(file) - 4;
	if (ft_strncmp(file, ".fdf", 4) != 0)
		return (0);
	return (1);
}

static int	get_dims(int fd, t_map *map)
{
	char	*l;
	char	**sp;
	int		tw;

	l = get_next_line(fd);
	map->w = -1;
	map->h = 0;
	while (l)
	{
		tw = 0;
		map->h++;
		sp = ft_split(l, ' ');
		free(l);
		if (!sp)
			return (0);
		while (sp[tw])
			tw++;
		free_strarr(sp);
		if (map->w != -1 && tw != map->w)
			return (0);
		map->w = tw;
		l = get_next_line(fd);
	}
	return (1);
}

static int	parse_line(int fd, t_map *map)
{
	int		i;
	int		j;
	char	*l;
	char	**sp;

	i = 0;
	l = get_next_line(fd);
	while (l)
	{
		if (!l)
			return (0);
		sp = ft_split(l, ' ');
		if (!sp)
			return (free_ret(l, 0));
		j = 0;
		while (j < map->w)
		{
			map->grid[i][j].value = ft_atoi(sp[j]);
			j++;
		}
		free(l);
		free_strarr(sp);
		l = get_next_line(fd);
		i++;
	}
	return (1);
}

static void	get_minmax(t_map *map)
{
	int	h;
	int	w;

	map->max = map->grid[0][0].value;
	map->min = map->grid[0][0].value;
	h = 0;
	while (h < map->h)
	{
		w = 0;
		while (w < map->w)
		{
			if (map->grid[h][w].value > map->max)
				map->max = map->grid[h][w].value;
			if (map->grid[h][w].value < map->min)
				map->min = map->grid[h][w].value;
			w++;
		}
		h++;
	}
	map->range = (long)map->max - (long)map->min;
}

int	parse_map(char *file, t_map *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || !get_dims(fd, map) || map->w == -1
		|| !name_check(file) || map->w > 5000 || map->h > 5000
		|| !alloc_map(map))
	{
		skip_line(fd);
		if (fd != -1)
			close(fd);
		return (0);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free_grid(map, 0));
	if (!parse_line(fd, map))
	{
		close(fd);
		return (free_grid(map, 0));
	}
	close(fd);
	get_minmax(map);
	return (1);
}
