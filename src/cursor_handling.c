/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:03:51 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:47:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	adjust_rotation(t_vec2 movement, t_fdf *fdf)
{
	fdf->yaw -= (double)movement.x / 300;
	if (fdf->yaw > 2 * M_PI)
		fdf->yaw -= 2 * M_PI;
	if (fdf->yaw < 0)
		fdf->yaw += 2 * M_PI;
	fdf->pitch -= (double)movement.y / 300;
	fdf->pitch = fmax(fmin(fdf->pitch, M_PI), 0);
}

void	handle_cursor_event(double cursor_x, double cursor_y, void *param)
{
	t_fdf	*fdf;
	t_vec2	movement;

	fdf = param;
	fdf->clicked = 0;
	if (!mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_MIDDLE)
		&& !mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_RIGHT))
		return ;
	movement.x = cursor_x - fdf->initial_cursor_pos.x;
	movement.y = cursor_y - fdf->initial_cursor_pos.y;
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_MIDDLE))
		fdf->height_scale -= (double)movement.y / 500;
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_RIGHT))
		adjust_rotation(movement, fdf);
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (!fdf->orthographic)
			movement = (t_vec2){movement.x * 3.3333, movement.y * 3.3333};
		fdf->mesh_position.x += movement.x;
		fdf->mesh_position.y += movement.y;
	}
	if (CURSOR_SETTABLE)
		mlx_set_mouse_pos(fdf->mlx, fdf->initial_cursor_pos.x, fdf->initial_cursor_pos.y);
	else
		fdf->initial_cursor_pos = (t_ivec2){cursor_x, cursor_y};
}