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

void	initialize_settings(t_fdf *fdf)
{
	fdf->mesh_scale = ft_imin(fdf->mlx->width, fdf->mlx->height);
	fdf->mesh_scale /= ft_imax(fdf->mesh_width, fdf->mesh_height)
		+ ft_imax(fdf->max_height, -fdf->min_height);
	fdf->mesh_scale = fmax(fdf->mesh_scale * 0.6, 0.01);
	if (!fdf->orthographic)
		fdf->mesh_scale *= 3.3333;
	fdf->line_thickness = 1;
	fdf->vertex_size = 1;
	fdf->dot_size = 1;
	fdf->dot_density = 1;
	fdf->draw_skybox = 1;
	fdf->camera_height = 2500;
	fdf->focus = 750;
	fdf->yaw = M_PI / 180 * 45;
	fdf->pitch = M_PI / 180 * (90 - 35.264);
	fdf->skybox_number = 1;
	fdf->height_scale *= fmax((double)ft_imax(fdf->mesh_width, fdf->mesh_height) / 1024, 1);
}

void	initialize_mlx(t_fdf *fdf)
{
	int32_t	width;
	int32_t	height;

	fdf->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FdF", 1);
	if (!fdf->mlx)
		exit_program("mlx_init failed", fdf);
	mlx_get_monitor_size(0, &width, &height);
	if (width < WINDOW_WIDTH || height < WINDOW_HEIGHT)
	{
		mlx_terminate(fdf->mlx);
		width = ft_imin(width, height) * 0.7;
		height = width;
		fdf->mlx = mlx_init(width, height, "FdF", 1);
		if (!fdf->mlx)
			exit_program("mlx_init failed", fdf);
	}
	fdf->depth_map = mlx_new_image(fdf->mlx, fdf->mlx->width, fdf->mlx->height);
	if (!fdf->depth_map)
		exit_program("mlx_new_image failed", fdf);
	fdf->background = mlx_new_image(fdf->mlx, fdf->mlx->width, fdf->mlx->height);
	if (!fdf->background || mlx_image_to_window(fdf->mlx, fdf->background, 0, 0) < 0)
		exit_program("mlx_new_image failed", fdf);
	fdf->canvas = mlx_new_image(fdf->mlx, fdf->mlx->width, fdf->mlx->height);
	if (!fdf->canvas || mlx_image_to_window(fdf->mlx, fdf->canvas, 0, 0) < 0)
		exit_program("mlx_new_image failed", fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	errno = 0;
	ft_bzero(&fdf, sizeof(t_fdf));
	if (argc != 2 && argc != 3)
		exit_program("Wrong number of arguments! Allowed: 1 or 2", &fdf);
	initialize_mesh(argc, argv, &fdf);
	initialize_skybox(&fdf);
	initialize_mlx(&fdf);
	initialize_settings(&fdf);
	initialize_hooks(&fdf);
	free_skybox_textures(&fdf);
	if (fdf.fps_image)
		mlx_delete_image(fdf.mlx, fdf.fps_image);
	mlx_terminate(fdf.mlx);
	free(fdf.mesh);
}