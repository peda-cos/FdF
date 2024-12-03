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

void	update_draw_mode(mlx_key_data_t key_data, t_fdf *fdf)
{
	if (key_data.action != MLX_PRESS)
		return ;
	if (key_data.key >= MLX_KEY_1 && key_data.key <= MLX_KEY_6)
	{
		fdf->draw_vertices = 0;
		fdf->draw_edges = 0;
		fdf->draw_dotted_edges = 0;
		fdf->draw_faces = 0;
		fdf->draw_faces_with_edges = 0;
	}
	if (key_data.key == MLX_KEY_1)
		fdf->draw_vertices = 1;
	if (key_data.key == MLX_KEY_2)
		fdf->draw_dotted_edges = 1;
	if (key_data.key == MLX_KEY_3)
		fdf->draw_edges = 1;
	if (key_data.key == MLX_KEY_4 || key_data.key == MLX_KEY_5)
		fdf->draw_faces = 1;
	if (key_data.key == MLX_KEY_5)
		fdf->draw_faces_with_edges = 1;
	if (key_data.key == MLX_KEY_A && fdf->draw_edges)
		fdf->anti_aliasing = !fdf->anti_aliasing;
	if (key_data.key == MLX_KEY_F)
		fdf->display_fps = !fdf->display_fps;
}

void	update_projection(mlx_key_data_t key_data, t_fdf *fdf)
{
	if (key_data.action != MLX_PRESS)
		return ;
	if (key_data.key == MLX_KEY_I)
	{
		fdf->yaw = M_PI / 180 * 45;
		fdf->pitch = M_PI / 180 * (90 - 35.264);
	}
	if (key_data.key == MLX_KEY_P && fdf->orthographic)
	{
		fdf->orthographic = 0;
		fdf->mesh_scale *= fdf->focus / (fdf->camera_height / 11.1111);
		fdf->mesh_position.x *= 3.3333;
		fdf->mesh_position.y *= 3.3333;
	}
	if ((key_data.key == MLX_KEY_O || key_data.key == MLX_KEY_I) && !fdf->orthographic)
	{
		fdf->orthographic = 1;
		fdf->mesh_scale /= fdf->focus / (fdf->camera_height / 11.1111);
		fdf->mesh_position.x /= 3.3333;
		fdf->mesh_position.y /= 3.3333;
	}
	if (key_data.key == MLX_KEY_R)
		fdf->mesh_position = (t_vec2){0, 0};
}

void	adjust_line_and_dot_size(mlx_key_data_t key_data, t_fdf *fdf)
{
	if (key_data.key == MLX_KEY_DOWN && key_data.action)
	{
		if (fdf->draw_edges && !fdf->anti_aliasing)
			fdf->line_thickness = ft_imax(fdf->line_thickness - 2, 1);
		else if (fdf->draw_dotted_edges)
			fdf->dot_size = ft_imax(fdf->dot_size - 2, 1);
		else if (fdf->draw_vertices)
			fdf->vertex_size = ft_imax(fdf->vertex_size - 2, 1);
	}
	if (key_data.key == MLX_KEY_UP && key_data.action)
	{
		if (fdf->draw_edges && !fdf->anti_aliasing)
			fdf->line_thickness = ft_imax(fdf->line_thickness + 2, 1);
		else if (fdf->draw_dotted_edges)
			fdf->dot_size = ft_imax(fdf->dot_size + 2, 1);
		else if (fdf->draw_vertices)
			fdf->vertex_size = ft_imax(fdf->vertex_size + 2, 1);
	}
	if (key_data.key == MLX_KEY_LEFT && key_data.action && fdf->draw_dotted_edges)
		fdf->dot_density = ft_imax(fdf->dot_density - 1, 1);
	if (key_data.key == MLX_KEY_RIGHT && key_data.action && fdf->draw_dotted_edges)
		fdf->dot_density = ft_imax(fdf->dot_density + 1, 1);
}

void	update_skybox(mlx_key_data_t key_data, t_fdf *fdf)
{
	if (key_data.key == MLX_KEY_S && key_data.action == MLX_PRESS)
	{
		if (key_data.modifier == MLX_SHIFT)
			fdf->draw_skybox = !fdf->draw_skybox;
		else
		{
			fdf->skybox_number++;
			if (fdf->skybox_number > 3)
				fdf->skybox_number = 1;
			load_skybox_textures(fdf->skybox_number, fdf);
			fdf->draw_skybox = 1;
		}
	}
}

void	handle_key_event(mlx_key_data_t key_data, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx);
	update_draw_mode(key_data, fdf);
	update_projection(key_data, fdf);
	update_skybox(key_data, fdf);
	if (key_data.modifier != MLX_SHIFT)
		adjust_line_and_dot_size(key_data, fdf);
	else if (key_data.key == MLX_KEY_UP && key_data.action)
		fdf->height_scale += 0.025;
	else if (key_data.key == MLX_KEY_DOWN && key_data.action)
		fdf->height_scale -= 0.025;
}