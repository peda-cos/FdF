/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:46:02 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/24 14:46:04 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	handle_escape(t_data *data)
{
	free_map(data->map);
	mlx_close_window(data->mlx->window);
	mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}

static void	handle_shift(t_data *data, int dx, int dy)
{
	data->shift_x += dx;
	data->shift_y += dy;
	render_map(data->map, data->mlx, data->window);
}

static void	handle_zoom(t_data *data, int delta)
{
	data->scale += delta;
	render_map(data->map, data->mlx, data->window);
}

static void	handle_rotation(t_data *data, float delta)
{
	data->angle += delta;
	render_map(data->map, data->mlx, data->window);
}

static void	handle_reset(t_data *data)
{
	set_projection_parameters(data);
	render_map(data->map, data->mlx, data->window);
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		handle_escape(data);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		handle_shift(data, 0, -10);
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		handle_shift(data, 0, 10);
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		handle_zoom(data, 1);
	else if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		handle_zoom(data, -1);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		handle_reset(data);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		handle_rotation(data, -0.1);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		handle_rotation(data, 0.1);
}

void	setup_hooks(mlx_t *mlx, t_data *data)
{
	mlx_key_hook(mlx, handle_key, data);
}
