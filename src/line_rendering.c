#include "../inc/fdf.h"

uint8_t	is_line_visible(t_pixel start, t_pixel end, t_fdf *fdf)
{
	int32_t	canvas_width;
	int32_t	canvas_height;
	int32_t	visibility_limit;

	canvas_width = fdf->canvas->width;
	canvas_height = fdf->canvas->height;
	if ((start.x > canvas_width && end.x > canvas_width) || (start.x < 0 && end.x < 0))
		return (0);
	if ((start.y > canvas_height && end.y > canvas_height) || (start.y < 0 && end.y < 0))
		return (0);
	visibility_limit = fdf->orthographic ? 500000 : 50000;
	canvas_width += visibility_limit;
	canvas_height += visibility_limit;
	if (start.y > canvas_height || start.x > canvas_width || start.y < -visibility_limit || start.x < -visibility_limit)
		return (0);
	if (end.y > canvas_height || end.x > canvas_width || end.y < -visibility_limit || end.x < -visibility_limit)
		return (0);
	return (1);
}

void	draw_anti_aliased_line_segment(t_vec2 position, t_pixel pixel, t_fdf *fdf)
{
	t_vec2		offset;
	double		alpha_factor;
	uint8_t		original_alpha;

	original_alpha = pixel.channel[A];
	pixel.pos = (t_ivec2){round(position.x), round(position.y)};
	offset = (t_vec2){position.x - pixel.x, position.y - pixel.y};
	alpha_factor = 1 - fabs(offset.x) - fabs(offset.y);
	pixel.channel[A] = original_alpha * alpha_factor;
	put_aa_pixel(fdf->canvas, pixel, fdf);
	if (!offset.x && !offset.y)
		return ;
	if (offset.x)
		pixel.x += offset.x / fabs(offset.x);
	else if (offset.y)
		pixel.y += offset.y / fabs(offset.y);
	pixel.channel[A] = original_alpha - pixel.channel[A];
	put_aa_pixel(fdf->canvas, pixel, fdf);
}

void	draw_anti_aliased_line(t_pixel start, t_pixel end, t_fdf *fdf)
{
	t_pixel		current_pixel;
	t_vec2		step;
	t_ivec2		delta;
	uint32_t	total_steps;
	uint32_t	step_index;

	step_index = 0;
	delta = (t_ivec2){end.x - start.x, end.y - start.y};
	total_steps = ft_imax(abs(delta.x), abs(delta.y));
	if (total_steps)
		step = (t_vec2){(double)delta.x / total_steps, (double)delta.y / total_steps};
	else
		put_pixel(fdf->canvas, start, 1, fdf);
	while (total_steps && step_index <= total_steps)
	{
		current_pixel.color = fade_color(start.color, end.color, total_steps, step_index);
		current_pixel.depth = start.depth + (end.depth - start.depth) * ((double)1 / total_steps) * step_index;
		draw_anti_aliased_line_segment(
			(t_vec2){start.x + step.x * step_index, start.y + step.y * step_index},
			current_pixel, fdf);
		step_index++;
	}
}

void	draw_pixel_line(t_pixel start, t_pixel end, uint8_t thickness, t_fdf *fdf)
{
	t_pixel		current_pixel;
	t_vec2		step;
	t_ivec2		delta;
	uint32_t	total_steps;
	uint32_t	step_index;

	current_pixel = start;
	step_index = 0;
	delta = (t_ivec2){end.x - start.x, end.y - start.y};
	total_steps = ft_imax(abs(delta.x), abs(delta.y));
	if (total_steps)
		step = (t_vec2){(double)delta.x / total_steps, (double)delta.y / total_steps};
	else
		put_pixel(fdf->canvas, start, thickness, fdf);
	while (total_steps && step_index <= total_steps)
	{
		current_pixel.pos = (t_ivec2){round(start.x + step.x * step_index), round(start.y + step.y * step_index)};
		current_pixel.color = fade_color(start.color, end.color, total_steps, step_index);
		current_pixel.depth = start.depth + (end.depth - start.depth) * ((double)1 / total_steps) * step_index;
		put_pixel(fdf->canvas, current_pixel, thickness, fdf);
		step_index++;
	}
}

void	draw_line(t_pixel start, t_pixel end, uint8_t thickness, t_fdf *fdf)
{
	if (!is_line_visible(start, end, fdf) || !start.visible || !end.visible)
		return ;
	if (!start.channel[A] && !end.channel[A])
		return ;
	if (fdf->anti_aliasing && fdf->draw_edges)
		draw_anti_aliased_line(start, end, fdf);
	else
		draw_pixel_line(start, end, thickness, fdf);
}