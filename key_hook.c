/* ************************************************************************** */

/*                                                                            */

/*                                                        :::      ::::::::   */

/*   key_hook.c                                         :+:      :+:    :+:   */

/*                                                    +:+ +:+
	+:+     */

/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+
	+#+        */

/*                                                +#+#+#+#+#+
	+#+            */

/*   Created: 2024/11/15 20:22:05 by peda-cos          #+#    #+#              */

/*   Updated: 2024/12/16 23:00:00 by peda-cos         ###   ########.fr        */

/*                                                                            */

/* ************************************************************************** */

#include "fdf.h"


void	handle_key_event(mlx_key_data_t key_data, void *param)
{
	t_mlx *mlx_instance;
	t_rotation rotation;

	mlx_instance = (t_mlx *)param;
	rotation = (t_rotation){0.0, 0.0, 0.0};
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
		cleanup_exit(mlx_instance, EXIT_SUCCESS);
	if (key_data.key == MLX_KEY_W && key_data.action == MLX_PRESS)
		rotation.x_angle = -M_PI / 16;
	if (key_data.key == MLX_KEY_S && key_data.action == MLX_PRESS)
		rotation.x_angle = M_PI / 16;
	if (key_data.key == MLX_KEY_A && key_data.action == MLX_PRESS)
		rotation.y_angle = -M_PI / 16;
	if (key_data.key == MLX_KEY_D && key_data.action == MLX_PRESS)
		rotation.y_angle = M_PI / 16;
	if (rotation.x_angle || rotation.y_angle || rotation.z_angle)
		rotate_map(mlx_instance, mlx_instance->map, rotation);
	draw_grid(mlx_instance, mlx_instance->map);
}
