#include "../inc/fdf.h"

void	render_mesh_dotted_edges(t_fdf *fdf)
{
	size_t	index;
	size_t	next_row_index;

	index = 0;
	next_row_index = fdf->mesh_width;
	while (index < fdf->vertex_count)
	{
		if (index % fdf->mesh_width)
			draw_dotted_line(fdf->vertices[index], fdf->vertices[index - 1], fdf->dot_size, fdf);
		if (next_row_index < fdf->vertex_count)
			draw_dotted_line(fdf->vertices[index], fdf->vertices[next_row_index], fdf->dot_size, fdf);
		index++;
		next_row_index++;
	}
}

void	render_mesh_faces(t_fdf *fdf)
{
	size_t	index;
	size_t	next_row_index;

	index = 0;
	next_row_index = fdf->mesh_width;
	while (next_row_index < fdf->vertex_count)
	{
		if (index % fdf->mesh_width && fdf->vertices[index - 1].pixel.visible
			&& fdf->vertices[index].pixel.visible && fdf->vertices[next_row_index - 1].pixel.visible
			&& fdf->vertices[next_row_index].pixel.visible)
		{
			render_face((t_face){fdf->vertices[index - 1], fdf->vertices[index],
				fdf->vertices[next_row_index], fdf->vertices[next_row_index - 1]}, fdf);
		}
		index++;
		next_row_index++;
	}
}

void	render_mesh_edges(t_fdf *fdf)
{
	size_t	index;
	size_t	next_row_index;

	index = 0;
	next_row_index = fdf->mesh_width;
	while (index < fdf->vertex_count)
	{
		if (index % fdf->mesh_width)
			draw_line(fdf->vertices[index].pixel, fdf->vertices[index - 1].pixel, fdf->line_thickness, fdf);
		if (next_row_index < fdf->vertex_count)
			draw_line(fdf->vertices[index].pixel, fdf->vertices[next_row_index].pixel, fdf->line_thickness, fdf);
		index++;
		next_row_index++;
	}
}

void	render_mesh_vertices(t_fdf *fdf)
{
	size_t	index;

	index = 0;
	while (index < fdf->vertex_count)
	{
		if (fdf->vertex_size <= 1 && fdf->vertices[index].pixel.visible)
			put_pixel(fdf->canvas, fdf->vertices[index].pixel, 1, fdf);
		else if (fdf->vertices[index].pixel.visible
			&& fdf->vertices[index].pixel.x + fdf->vertex_size + 2 >= 0
			&& fdf->vertices[index].pixel.y + fdf->vertex_size + 2 >= 0
			&& fdf->vertices[index].pixel.x - fdf->vertex_size - 2 <= (int)fdf->canvas->width
			&& fdf->vertices[index].pixel.y - fdf->vertex_size - 2 <= (int)fdf->canvas->height)
			put_dot(fdf->canvas, fdf->vertices[index].pixel, fdf->vertex_size, fdf);
		index++;
	}
}

void	render_mesh(t_fdf *fdf)
{
	ft_bzero(fdf->canvas->pixels, fdf->canvas->width * fdf->canvas->height * 4);
	if (fdf->draw_vertices || fdf->draw_dotted_edges || fdf->draw_edges || fdf->draw_faces)
		project_mesh(fdf);
	if (fdf->draw_vertices)
		render_mesh_vertices(fdf);
	else if (fdf->draw_edges)
		render_mesh_edges(fdf);
	else if (fdf->draw_dotted_edges)
		render_mesh_dotted_edges(fdf);
	else if (fdf->draw_faces)
		render_mesh_faces(fdf);
}