#include "../inc/fdf.h"

t_ivec2	interpolate_position(t_ivec2 start, t_ivec2 end, double factor)
{
	t_ivec2	result;

	result.x = start.x + ((end.x - start.x) * factor);
	result.y = start.y + ((end.y - start.y) * factor);
	return (result);
}

void	draw_dotted_line(t_vertex vertex_a, t_vertex vertex_b, uint16_t dot_size, t_fdf *fdf)
{
	double		distance;
	double		factor;
	double		initial_factor;
	t_pixel		dot_pixel;
	uint32_t	segments;

	if (!vertex_a.pixel.visible || !vertex_b.pixel.visible 
		|| !line_is_visible(vertex_a.pixel, vertex_b.pixel, fdf))
		return ;
	put_dot(fdf->canvas, vertex_a.pixel, dot_size, fdf);
	put_dot(fdf->canvas, vertex_b.pixel, dot_size, fdf);
	if (!(vertex_b.z - vertex_a.z) && fdf->dot_density <= 1)
		return ;
	distance = fmax(fabs((vertex_b.z - vertex_a.z) * fdf->height_scale), 1);
	segments = round(distance) * fdf->dot_density;
	dot_pixel = vertex_a.pixel;
	initial_factor = (double)1 / segments;
	factor = initial_factor;
	while (factor < 1)
	{
		dot_pixel.pos = interpolate_position(vertex_a.pixel.pos, vertex_b.pixel.pos, factor);
		dot_pixel.color = interpolate_color(vertex_a.pixel.color, vertex_b.pixel.color, factor);
		dot_pixel.depth = vertex_a.pixel.depth + ((vertex_b.pixel.depth - vertex_a.pixel.depth) * factor);
		put_dot(fdf->canvas, dot_pixel, dot_size, fdf);
		factor += initial_factor;
	}
}

void	update_pixel_position(t_ivec2 *position, t_ivec2 *index, uint16_t size)
{
	(*position).x++;
	(*index).x++;
	if ((*index).x == size)
	{
		(*position).y++;
		(*index).y++;
		(*position).x -= size;
		(*index).x = 0;
	}
}

void	put_dot(mlx_image_t *image, t_pixel pixel, uint16_t dot_size, t_fdf *fdf)
{
	t_ivec2	index;
	t_ivec2	center;
	double	radius;
	double	distance;
	t_color	color;

	if (!fdf->orthographic && dot_size > 1)
		dot_size = fmax(dot_size * fdf->camera_height / pixel.depth, 1);
	index = (t_ivec2){0, 0};
	center = pixel.pos;
	radius = (double)dot_size / 2;
	color.color = pixel.color;
	pixel.pos = (t_ivec2){pixel.x - dot_size / 2, pixel.y - dot_size / 2};
	while (index.y <= dot_size)
	{
		distance = get_length(pixel.pos, center);
		if (distance <= radius)
		{
			pixel.channel[R] = (1 - distance / radius / 2) * color.channel[R];
			pixel.channel[G] = (1 - distance / radius / 2) * color.channel[G];
			pixel.channel[B] = (1 - distance / radius / 2) * color.channel[B];
			put_pixel(image, pixel, 1, fdf);
		}
		update_pixel_position(&pixel.pos, &index, dot_size + 1);
	}
}