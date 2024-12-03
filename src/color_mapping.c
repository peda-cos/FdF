#include "../inc/fdf.h"

int32_t	calculate_height_color(int32_t height, t_fdf *fdf)
{
	t_color	color;
	double	factor;

	factor = 0;
	if (fdf->max_height - fdf->min_height)
	{
		factor = (height - fdf->min_height);
		factor /= (fdf->max_height - fdf->min_height);
	}
	color.color = lerp_color(0xFDD404FF, 0xF40AD8FF, factor);
	return (color.color);
}

void	determine_min_max_height(t_fdf *fdf)
{
	uint32_t	index;

	fdf->min_height = fdf->mesh[0].z;
	fdf->max_height = fdf->mesh[0].z;
	index = 0;
	while (index < fdf->vertex_count)
	{
		if (fdf->mesh[index].z > fdf->max_height)
			fdf->max_height = fdf->mesh[index].z;
		if (fdf->mesh[index].z < fdf->min_height)
			fdf->min_height = fdf->mesh[index].z;
		index++;
	}
}

void	apply_vertex_colors(t_fdf *fdf)
{
	size_t	index;

	determine_min_max_height(fdf);
	index = 0;
	while (index < fdf->vertex_count)
	{
		fdf->mesh[index].pixel.color = calculate_height_color(fdf->mesh[index].z, fdf);
		index++;
	}
}