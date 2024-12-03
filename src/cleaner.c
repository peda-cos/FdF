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

void	free_skybox_textures(t_fdf *fdf)
{
	if (fdf->skybox.back_texture)
		mlx_delete_texture(fdf->skybox.back_texture);
	fdf->skybox.back_texture = NULL;

	if (fdf->skybox.down_texture)
		mlx_delete_texture(fdf->skybox.down_texture);
	fdf->skybox.down_texture = NULL;

	if (fdf->skybox.front_texture)
		mlx_delete_texture(fdf->skybox.front_texture);
	fdf->skybox.front_texture = NULL;

	if (fdf->skybox.left_texture)
		mlx_delete_texture(fdf->skybox.left_texture);
	fdf->skybox.left_texture = NULL;

	if (fdf->skybox.right_texture)
		mlx_delete_texture(fdf->skybox.right_texture);
	fdf->skybox.right_texture = NULL;

	if (fdf->skybox.up_texture)
		mlx_delete_texture(fdf->skybox.up_texture);
	fdf->skybox.up_texture = NULL;
}

void	exit_program(char *error_message, t_fdf *fdf)
{
	free_skybox_textures(fdf);

	if (fdf->mlx)
		mlx_terminate(fdf->mlx);

	if (fdf->mesh)
		free(fdf->mesh);

	if (errno)
		perror(error_message);
	else
	{
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}