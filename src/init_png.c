#include "fdf.h"

void	center_mesh_z_axis(t_FdF *fdf_data)
{
	u_int32_t	vertex_index;
	u_int32_t	height_offset;

	vertex_index = 0;
	set_min_max_height(fdf_data);
	height_offset = fdf_data->min_height + ((fdf_data->max_height - fdf_data->min_height) / 2);
	while (vertex_index < fdf_data->vertex_count)
	{
		fdf_data->mesh[vertex_index].z -= height_offset;
		vertex_index++;
	}
}

void	populate_mesh_from_png(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_FdF *fdf_data)
{
	u_int32_t	vertex_index;
	u_int32_t	current_x;
	u_int32_t	current_y;

	vertex_index = 0;
	current_x = 0;
	current_y = 0;
	while (vertex_index < fdf_data->vertex_count)
	{
		fdf_data->mesh[vertex_index].x = current_x;
		fdf_data->mesh[vertex_index].y = current_y;
		fdf_data->mesh[vertex_index].z = heightmap->pixels[vertex_index * 4];
		if (colormap)
			fdf_data->mesh[vertex_index].pixel.color = sample_texture(colormap, current_x, current_y);
		vertex_index++;
		current_x++;
		if (current_x == heightmap->width)
		{
			current_x = 0;
			current_y++;
		}
	}
	if (!colormap)
		set_vertex_colors(fdf_data);
	center_mesh_z_axis(fdf_data);
}

void	validate_and_set_dimensions(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_FdF *fdf_data)
{
	if (colormap && (heightmap->width != colormap->width || heightmap->height != colormap->height))
	{
		mlx_delete_texture(heightmap);
		mlx_delete_texture(colormap);
		clean_exit("Both images need to have the same resolution!", fdf_data);
	}
	fdf_data->mesh_width = heightmap->width;
	fdf_data->mesh_height = heightmap->height;
	fdf_data->vertex_count = heightmap->width * heightmap->height;
}

void	allocate_mesh_memory(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_FdF *fdf_data)
{
	fdf_data->mesh = (t_vert *)malloc(fdf_data->vertex_count * sizeof(t_vert));
	if (!fdf_data->mesh)
	{
		mlx_delete_texture(heightmap);
		if (colormap)
			mlx_delete_texture(colormap);
		clean_exit("Memory allocation failed", fdf_data);
	}
}

void	initialize_from_png(char *heightmap_file, char *colormap_file, t_FdF *fdf_data)
{
	mlx_texture_t	*heightmap;
	mlx_texture_t	*colormap;

	colormap = NULL;
	heightmap = mlx_load_png(heightmap_file);
	if (!heightmap)
		clean_exit(heightmap_file, fdf_data);
	if (colormap_file)
	{
		colormap = mlx_load_png(colormap_file);
		if (!colormap)
		{
			mlx_delete_texture(heightmap);
			clean_exit(colormap_file, fdf_data);
		}
	}
	validate_and_set_dimensions(heightmap, colormap, fdf_data);
	allocate_mesh_memory(heightmap, colormap, fdf_data);
	populate_mesh_from_png(heightmap, colormap, fdf_data);
	mlx_delete_texture(heightmap);
	if (colormap)
		mlx_delete_texture(colormap);
	fdf_data->height_scale = 1;
	if (!ft_strncmp(heightmap_file, "assets/maps/materials/", 22))
		fdf_data->height_scale = 0.2;
}