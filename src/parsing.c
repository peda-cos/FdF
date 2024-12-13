/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:24:20 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:24:21 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int  map_dims(int fd, t_map *mp);
static int  parse_line(int fd, t_map *mp);
static void find_map_minmax(t_map *mp);
static int  valid_name(char *f);

int parse_map(char *f, t_map *mp)
{
	int fd;

	fd = open(f, O_RDONLY);
	if (fd == -1 || !map_dims(fd, mp) || mp->w == -1 ||
		!valid_name(f) || mp->w > 5000 || mp->h > 5000 || !alloc_map(mp))
	{
		skip_line(fd);
		if (fd != -1)
			close(fd);
		return (0);
	}
	close(fd);
	fd = open(f, O_RDONLY);
	if (fd == -1)
		return (free_grid(mp, 0));
	if (!parse_line(fd, mp))
	{
		close(fd);
		return (free_grid(mp, 0));
	}
	close(fd);
	find_map_minmax(mp);
	return (1);
}

static int valid_name(char *f)
{
	if (ft_strlen(f) < 4)
		return (0);
	if (ft_strlen(f) == 4)
		if (ft_strncmp(f, ".fdf", ft_strlen(f)) != 0)
			return (0);
	f += ft_strlen(f) - 4;
	if (ft_strncmp(f, ".fdf", 4) != 0)
		return (0);
	return (1);
}

static int map_dims(int fd, t_map *mp)
{
	char    *l;
	char    **sp;
	int     tw;

	l = get_next_line(fd);
	mp->w = -1;
	mp->h = 0;
	while (l)
	{
		tw = 0;
		mp->h++;
		sp = ft_split(l, ' ');
		free(l);
		if (!sp)
			return (0);
		while (sp[tw])
			tw++;
		free_strarr(sp);
		if (mp->w != -1 && tw != mp->w)
			return (0);
		mp->w = tw;
		l = get_next_line(fd);
	}
	return (1);
}

static int parse_line(int fd, t_map *mp)
{
	int     i;
	int     j;
	char    *l;
	char    **sp;

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
		while (j < mp->w)
		{
			mp->grid[i][j].value = ft_atoi(sp[j]);
			j++;
		}
		free(l);
		free_strarr(sp);
		l = get_next_line(fd);
		i++;
	}
	return (1);
}

static void find_map_minmax(t_map *mp)
{
	int h;
	int w;

	mp->max = mp->grid[0][0].value;
	mp->min = mp->grid[0][0].value;
	h = 0;
	while (h < mp->h)
	{
		w = 0;
		while (w < mp->w)
		{
			if (mp->grid[h][w].value > mp->max)
				mp->max = mp->grid[h][w].value;
			if (mp->grid[h][w].value < mp->min)
				mp->min = mp->grid[h][w].value;
			w++;
		}
		h++;
	}
	mp->range = (long)mp->max - (long)mp->min;
}
