/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:03:51 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:47:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_scroll_event(double offset, double scroll, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (offset || mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_SHIFT)
		|| mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT_SHIFT))
	{
		fdf->focus += (offset + scroll) * (fdf->focus / 100);
		fdf->focus = fmin(fmax(fdf->focus, 300), 50000);
		fdf->camera_height = fdf->focus * 3.3333;
	}
	else
	{
		scroll = fmin((1500 - fdf->mesh_scale) / 100, scroll);
		fdf->initial_mesh_scale = fdf->mesh_scale;
		fdf->mesh_scale += (fdf->mesh_scale / 100) * scroll;
		fdf->mesh_scale = fmin(fmax(fdf->mesh_scale, 0.01), 1500);
		fdf->mesh_position.x *= (1 + scroll / 100);
		fdf->mesh_position.y *= (1 + scroll / 100);
		if (fdf->vertex_size > 1)
			fdf->vertex_size *= fdf->mesh_scale / fdf->initial_mesh_scale;
		fdf->vertex_size = fmax(fdf->vertex_size, 1);
		if (fdf->dot_size > 1)
			fdf->dot_size *= fdf->mesh_scale / fdf->initial_mesh_scale;
		fdf->dot_size = fmax(fdf->dot_size, 1);
	}
}

void	handle_mouse_event(enum mouse_key button, enum action action,
						enum modifier_key modifier, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (action == MLX_PRESS && !modifier)
	{
		fdf->mouse_buttons_pressed++;
		if (button == MLX_MOUSE_BUTTON_LEFT && fdf->clicked)
			fdf->mesh_position = (t_vec2){0, 0};
		if (button == MLX_MOUSE_BUTTON_LEFT)
			fdf->clicked = 0.3;
		mlx_get_mouse_pos(fdf->mlx, &fdf->initial_cursor_position.x,
			&fdf->initial_cursor_position.y);
		mlx_set_cursor_mode(fdf->mlx, MLX_MOUSE_HIDDEN);
	}
	if (action == MLX_RELEASE && !modifier)
	{
		fdf->mouse_buttons_pressed = ft_imax(0, fdf->mouse_buttons_pressed - 1);
		if (!fdf->mouse_buttons_pressed)
		{
			mlx_set_cursor_mode(fdf->mlx, MLX_MOUSE_NORMAL);
			mlx_set_mouse_pos(fdf->mlx, fdf->initial_cursor_position.x,
				fdf->initial_cursor_position.y);
		}
	}
}

void	handle_resize_event(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_resize_image(fdf->depth_map, width, height);
	if (!fdf->depth_map)
		clean_exit("mlx_resize_image failed", fdf);
	mlx_resize_image(fdf->canvas, width, height);
	if (!fdf->canvas)
		clean_exit("mlx_resize_image failed", fdf);
	mlx_resize_image(fdf->background, width, height);
	if (!fdf->background)
		clean_exit("mlx_resize_image failed", fdf);
}

void	initialize_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, handle_key_event, fdf);
	mlx_mouse_hook(fdf->mlx, handle_mouse_event, fdf);
	mlx_cursor_hook(fdf->mlx, handle_cursor_event, fdf);
	mlx_scroll_hook(fdf->mlx, handle_scroll_event, fdf);
	mlx_resize_hook(fdf->mlx, handle_resize_event, fdf);
	mlx_loop_hook(fdf->mlx, main_loop, fdf);
	mlx_loop(fdf->mlx);
}