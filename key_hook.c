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

	mlx_instance = (t_mlx *)param;
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
		cleanup_exit(mlx_instance, EXIT_SUCCESS);
	if (key_data.key == MLX_KEY_UP && key_data.action == MLX_PRESS)
		move_map(mlx_instance, UP);
	if (key_data.key == MLX_KEY_DOWN && key_data.action == MLX_PRESS)
		move_map(mlx_instance, DOWN);
	if (key_data.key == MLX_KEY_LEFT && key_data.action == MLX_PRESS)
		move_map(mlx_instance, LEFT);
	if (key_data.key == MLX_KEY_RIGHT && key_data.action == MLX_PRESS)
		move_map(mlx_instance, RIGHT);
	if (key_data.key == MLX_KEY_W && key_data.action == MLX_PRESS)
		zoom_increase(mlx_instance);
	if (key_data.key == MLX_KEY_S && key_data.action == MLX_PRESS)
		zoom_decrease(mlx_instance);
	draw_grid(mlx_instance, mlx_instance->map);
}
