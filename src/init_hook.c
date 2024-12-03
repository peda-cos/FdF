#include "../inc/fdf.h"

void	scroll_hook(double scroll_delta, double scroll_amount, void *param)
{
	t_FdF	*fdf_data;

	fdf_data = param;
	if (scroll_delta || mlx_is_key_down(fdf_data->mlx, MLX_KEY_LEFT_SHIFT)
		|| mlx_is_key_down(fdf_data->mlx, MLX_KEY_RIGHT_SHIFT))
	{
		fdf_data->focal_length += (scroll_delta + scroll_amount) * (fdf_data->focal_length / 100);
		fdf_data->focal_length = fmin(fmax(fdf_data->focal_length, 300), 50000);
		fdf_data->camera_height = fdf_data->focal_length * 3.3333;
	}
	else
	{
		scroll_amount = fmin((1500 - fdf_data->mesh_scale) / 100, scroll_amount);
		fdf_data->initial_mesh_scale = fdf_data->mesh_scale;
		fdf_data->mesh_scale += (fdf_data->mesh_scale / 100) * scroll_amount;
		fdf_data->mesh_scale = fmin(fmax(fdf_data->mesh_scale, 0.01), 1500);
		fdf_data->mesh_position.x *= (1 + scroll_amount / 100);
		fdf_data->mesh_position.y *= (1 + scroll_amount / 100);
		if (fdf_data->vertex_size > 1)
			fdf_data->vertex_size *= fdf_data->mesh_scale / fdf_data->initial_mesh_scale;
		fdf_data->vertex_size = fmax(fdf_data->vertex_size, 1);
		if (fdf_data->dot_size > 1)
			fdf_data->dot_size *= fdf_data->mesh_scale / fdf_data->initial_mesh_scale;
		fdf_data->dot_size = fmax(fdf_data->dot_size, 1);
	}
}

void	mouse_hook(enum mouse_key mouse_button, enum action mouse_action,
				 enum modifier_key modifier_keys, void *param)
{
	t_FdF	*fdf_data;

	fdf_data = param;
	if (mouse_action == MLX_PRESS && !modifier_keys)
	{
		fdf_data->mouse_button_count++;
		if (mouse_button == MLX_MOUSE_BUTTON_LEFT && fdf_data->click_timer)
			fdf_data->mesh_position = (t_vec2){0, 0};
		if (mouse_button == MLX_MOUSE_BUTTON_LEFT)
			fdf_data->click_timer = 0.3;
		mlx_get_mouse_pos(fdf_data->mlx, &fdf_data->initial_cursor_pos.x, &fdf_data->initial_cursor_pos.y);
		mlx_set_cursor_mode(fdf_data->mlx, MLX_MOUSE_HIDDEN);
	}
	if (mouse_action == MLX_RELEASE && !modifier_keys)
	{
		fdf_data->mouse_button_count = ft_imax(0, fdf_data->mouse_button_count - 1);
		if (!fdf_data->mouse_button_count)
		{
			mlx_set_cursor_mode(fdf_data->mlx, MLX_MOUSE_NORMAL);
			mlx_set_mouse_pos(fdf_data->mlx, fdf_data->initial_cursor_pos.x,
							  fdf_data->initial_cursor_pos.y);
		}
	}
}

void	resize_hook(int32_t window_width, int32_t window_height, void *param)
{
	t_FdF	*fdf_data;

	fdf_data = param;
	mlx_resize_image(fdf_data->depth_map, window_width, window_height);
	if (!fdf_data->depth_map)
		clean_exit("mlx_resize_image failed", fdf_data);
	mlx_resize_image(fdf_data->canvas, window_width, window_height);
	if (!fdf_data->canvas)
		clean_exit("mlx_resize_image failed", fdf_data);
	mlx_resize_image(fdf_data->background, window_width, window_height);
	if (!fdf_data->background)
		clean_exit("mlx_resize_image failed", fdf_data);
}

void	init_hooks(t_FdF *fdf_data)
{
	mlx_key_hook(fdf_data->mlx, key_hook, fdf_data);
	mlx_mouse_hook(fdf_data->mlx, mouse_hook, fdf_data);
	mlx_cursor_hook(fdf_data->mlx, cursor_hook, fdf_data);
	mlx_scroll_hook(fdf_data->mlx, scroll_hook, fdf_data);
	mlx_resize_hook(fdf_data->mlx, resize_hook, fdf_data);
	mlx_loop_hook(fdf_data->mlx, main_loop, fdf_data);
	mlx_loop(fdf_data->mlx);
}
