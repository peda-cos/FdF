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

void	center_mesh_height(t_fdf *fdf)
{
	uint32_t	index;
	uint32_t	offset;

	index = 0;
	set_min_max_height(fdf);
	offset = fdf->min_height + ((fdf->max_height - fdf->min_height) / 2);
	while (index < fdf->vertex_count)
	{
		fdf->vertices[index].z -= offset;
		index++;
	}
}

void	parse_png_to_mesh(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_fdf *fdf)
{
	uint32_t	index;
	uint32_t	x;
	uint32_t	y;

	index = 0;
	x = 0;
	y = 0;
	while (index < fdf->vertex_count)
	{
		fdf->vertices[index].x = x;
		fdf->vertices[index].y = y;
		fdf->vertices[index].z = heightmap->pixels[index * 4];
		if (colormap)
			fdf->vertices[index].pixel.color = sample_texture(colormap, x, y);
		index++;
		x++;
		if (x == heightmap->width)
		{
			x = 0;
			y++;
		}
	}
	if (!colormap)
		set_vertex_colors(fdf);
	center_mesh_height(fdf);
}

void	validate_image_dimensions(
	mlx_texture_t *heightmap, mlx_texture_t *colormap, t_fdf *fdf)
{
	if (colormap && (heightmap->width != colormap->width
			|| heightmap->height != colormap->height))
	{
		mlx_delete_texture(heightmap);
		mlx_delete_texture(colormap);
		clean_exit("Both images need to have the same resolution!", fdf);
	}
	fdf->mesh_width = heightmap->width;
	fdf->mesh_height = heightmap->height;
	fdf->vertex_count = heightmap->width * heightmap->height;
}

void	allocate_mesh_memory(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_fdf *fdf)
{
	fdf->vertices = (t_vertex *)malloc(fdf->vertex_count * sizeof(t_vertex));
	if (!fdf->vertices)
	{
		mlx_delete_texture(heightmap);
		if (colormap)
			mlx_delete_texture(colormap);
		clean_exit("Memory allocation failed", fdf);
	}
}

void	initialize_from_png(char *heightmap_file, char *colormap_file, t_fdf *fdf)
{
	mlx_texture_t	*heightmap;
	mlx_texture_t	*colormap;

	colormap = NULL;
	heightmap = mlx_load_png(heightmap_file);
	if (!heightmap)
		clean_exit(heightmap_file, fdf);
	if (colormap_file)
	{
		colormap = mlx_load_png(colormap_file);
		if (!colormap)
		{
			mlx_delete_texture(heightmap);
			clean_exit(colormap_file, fdf);
		}
	}
	validate_image_dimensions(heightmap, colormap, fdf);
	allocate_mesh_memory(heightmap, colormap, fdf);
	parse_png_to_mesh(heightmap, colormap, fdf);
	mlx_delete_texture(heightmap);
	if (colormap)
		mlx_delete_texture(colormap);
	fdf->height_scale = 1;
	if (!ft_strncmp(heightmap_file, "assets/maps/materials/", 22))
		fdf->height_scale = 0.2;
}