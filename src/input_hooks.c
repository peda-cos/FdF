/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:00:22 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/28 21:36:32 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx_instance, &handle_exit, fdf);
	mlx_loop_hook(fdf->mlx_instance, &handle_translation, fdf);
	mlx_loop_hook(fdf->mlx_instance, &handle_zoom, fdf);
}

void	handle_exit(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx_instance);
}

void	handle_translation(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_W))
		fdf->camera->y_offset -= TRANSLATE_STEP;
	else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_S))
		fdf->camera->y_offset += TRANSLATE_STEP;
	else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_A))
		fdf->camera->x_offset -= TRANSLATE_STEP;
	else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_D))
		fdf->camera->x_offset += TRANSLATE_STEP;
	else
		return ;
	render_map(fdf);
}

void	handle_zoom(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_R))
	{
		reset_camera(fdf);
		render_map(fdf);
		return ;
	}
	if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_KP_ADD))
		fdf->camera->zoom_level *= 1.1;
	else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_KP_SUBTRACT))
		fdf->camera->zoom_level /= 1.1;
	else if (fdf->camera->zoom_level < 0.01)
		fdf->camera->zoom_level = 0.01;
	else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_J))
		fdf->camera->z_scale_factor *= 1.1;
	else if (mlx_is_key_down(fdf->mlx_instance, MLX_KEY_K))
		fdf->camera->z_scale_factor /= 1.1;
	else if (fdf->camera->z_scale_factor < 0.01)
		fdf->camera->z_scale_factor = 0.01;
	else
		return ;
	render_map(fdf);
}
