/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static int	parse_token_loop(char **tokens, t_map *map, int row)
{
	int	col;
	int	*z_row;
	int	*c_row;

	z_row = map->z_values[row];
	c_row = map->colors[row];
	col = 0;
	while (col < map->width && tokens[col])
	{
		if (parse_token(tokens[col], &z_row[col], &c_row[col]) < 0)
			return (-1);
		if (z_row[col] < map->z_min)
			map->z_min = z_row[col];
		if (z_row[col] > map->z_max)
			map->z_max = z_row[col];
		col++;
	}
	return (0);
}

int	parse_line(char *line, t_map *map, int row)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (-1);
	if (parse_token_loop(tokens, map, row) < 0)
	{
		free_split(tokens);
		return (-1);
	}
	free_split(tokens);
	return (0);
}
