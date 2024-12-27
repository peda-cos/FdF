#include "fdf.h"

void	set_line_parameters(t_draw_parameters *draw_params,
		t_line_coordinates *coords)
{
	draw_params->delta_x = get_axis_difference(coords->start_x, coords->end_x);
	draw_params->delta_y = get_axis_difference(coords->start_y, coords->end_y);
	draw_params->step_x = get_step_direction(coords->start_x, coords->end_x);
	draw_params->step_y = get_step_direction(coords->start_y, coords->end_y);
	draw_params->decision = (2 * draw_params->delta_y) - draw_params->delta_x;
	draw_params->current_x = coords->start_x;
	draw_params->current_y = coords->start_y;
}

void	set_map_offset(t_map_offset *offset, t_map_dimensions *map_dims)
{
	int	max_width_interval;
	int	max_height_interval;

	max_width_interval = WIDTH / map_dims->width;
	max_height_interval = HEIGHT / map_dims->height;
	if (max_width_interval < max_height_interval)
		offset->scaling_interval = max_width_interval;
	else
		offset->scaling_interval = max_height_interval;
	offset->start_x = (WIDTH - (map_dims->width * offset->scaling_interval))
		/ 2;
	offset->start_y = (HEIGHT - (map_dims->height * offset->scaling_interval))
		/ 2;
}

int	get_step_direction(float start_point, float end_point)
{
	if (end_point > start_point)
		return (1);
	else
		return (-1);
}

int	get_axis_difference(float start_point, float end_point)
{
	float	diff;

	diff = end_point - start_point;
	if (diff < 0)
		diff = -diff;
	return ((int)diff);
}
