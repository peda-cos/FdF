/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:46:13 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/24 14:46:13 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_projection_parameters(t_data *data)
{
	data->angle = 0.523599;
	data->scale = 20.0;
	data->shift_x = 400;
	data->shift_y = 300;
}

void	process_point(t_data *data, int y, int x)
{
	t_point	p1;
	t_point	p2;
	t_point	projected_p1;
	t_point	projected_p2;

	p1 = data->map->points[y][x];
	projected_p1 = project_iso(p1, data->angle, data->scale, data->shift_x, data->shift_y);
	if (x < data->map->width - 1)
	{
		p2 = data->map->points[y][x + 1];
		projected_p2 = project_iso(p2, data->angle, data->scale, data->shift_x, data->shift_y);
		draw_line(data->mlx, data->window, projected_p1, projected_p2);
	}
	if (y < data->map->height - 1)
	{
		p2 = data->map->points[y + 1][x];
		projected_p2 = project_iso(p2, data->angle, data->scale, data->shift_x, data->shift_y);
		draw_line(data->mlx, data->window, projected_p1, projected_p2);
	}
}

void	render_row(t_data *data, int y)
{
	int	x;

	x = 0;
	while (x < data->map->width)
	{
		process_point(data, y, x);
		x++;
	}
}

static void	initialize_render(t_data *data, t_map *map, mlx_t *mlx, mlx_image_t *window)
{
	data->map = map;
	data->mlx = mlx;
	data->window = window;
	set_projection_parameters(data);
}

void	render_map(t_map *map, mlx_t *mlx, mlx_image_t *window)
{
	t_data	data;
	int		y;

	initialize_render(&data, map, mlx, window);
	y = 0;
	while (y < map->height)
	{
		render_row(&data, y);
		y++;
	}
}
