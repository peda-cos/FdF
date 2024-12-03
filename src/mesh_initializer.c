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

void	adjust_mesh_to_center(t_fdf *fdf)
{
	t_vec2	center;
	size_t	index;

	center.x = (double)(fdf->map_width - 1) / 2;
	center.y = (double)(fdf->map_height - 1) / 2;
	index = 0;
	while (index < fdf->vertex_count)
	{
		fdf->vertices[index].x -= center.x;
		fdf->vertices[index].y -= center.y;
		index++;
	}
}

int8_t	is_fdf_file(char *file_path)
{
	if (ft_strrchr(file_path, '.'))
		if (!ft_strncmp(ft_strrchr(file_path, '.'), ".fdf\0", 5))
			return (1);
	return (0);
}

int8_t	is_png_file(char *file_path)
{
	if (ft_strrchr(file_path, '.'))
		if (!ft_strncmp(ft_strrchr(file_path, '.'), ".png\0", 5))
			return (1);
	return (0);
}

void	initialize_mesh(int argc, char **argv, t_fdf *fdf)
{
	if (argc == 2 && is_fdf_file(argv[1]))
	{
		initialize_fdf(argv[1], fdf);
		fdf->draw_edges = 1;
		fdf->anti_aliasing = 1;
		fdf->orthographic_projection = 1;
	}
	else if (argc == 2 && is_png_file(argv[1]))
		initialize_png(argv[1], NULL, fdf);
	else if (argc == 3 && is_png_file(argv[1]) && is_png_file(argv[2]))
		initialize_png(argv[1], argv[2], fdf);
	else
	{
		ft_putstr_fd("Invalid file format! Supported formats:\n", 2);
		ft_putstr_fd("- One .fdf file  (heightmap)\n", 2);
		ft_putstr_fd("- One .png file  (heightmap)\n", 2);
		ft_putstr_fd("- Two .png files (heightmap and colormap)\n", 2);
		exit(1);
	}
	if (!fdf->draw_edges)
		fdf->draw_vertices = 1;
	adjust_mesh_to_center(fdf);
}