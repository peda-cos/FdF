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

void	reset_depth_map(t_fdf *fdf)
{
	size_t	len;
	size_t	index;
	float	*depth_pixels;

	len = fdf->depth_map->width * fdf->depth_map->height;
	index = 0;
	depth_pixels = (float *)fdf->depth_map->pixels;
	while (index < len)
	{
		depth_pixels[index] = 9999999;
		index++;
	}
}

void	adjust_canvas_brightness(double factor, t_fdf *fdf)
{
	uint32_t	x;
	uint32_t	y;
	uint8_t		alpha;

	x = 0;
	y = 0;
	while (y < fdf->canvas->height)
	{
		alpha = fdf->canvas->pixels[x * 4 + y * fdf->canvas->width * 4 + 3];
		alpha = ft_imin(alpha * factor, 255);
		fdf->canvas->pixels[x * 4 + y * fdf->canvas->width * 4 + 3] = alpha;
		x++;
		if (x == fdf->canvas->width)
		{
			y++;
			x = 0;
		}
	}
}

void	render_background(t_fdf *fdf)
{
	uint32_t	x;
	uint32_t	y;
	t_color		color;

	color.color = 0x051525FF;
	x = 0;
	y = 0;
	while (y < fdf->background->height)
	{
		mlx_put_pixel(fdf->background, x, y, color.color);
		x++;
		if (x == fdf->background->width)
		{
			y++;
			color.channel[R] = y * 50 / fdf->background->height;
			x = 0;
		}
	}
}

void	display_fps(t_fdf *fdf)
{
	static uint32_t	frame_count;
	static double	elapsed_time;
	char			*fps_str;

	elapsed_time += fdf->mlx->delta_time;
	frame_count++;
	if (!fdf->fps_image)
		fdf->fps_image = mlx_put_string(fdf->mlx, "--", 7, 2);
	if (elapsed_time >= 1)
	{
		if (fdf->fps_image)
			mlx_delete_image(fdf->mlx, fdf->fps_image);
		fps_str = ft_itoa((int)(frame_count / elapsed_time));
		if (!fps_str)
			clean_exit("Allocation in ft_itoa failed", fdf);
		fdf->fps_image = mlx_put_string(fdf->mlx, fps_str, 7, 3);
		free(fps_str);
		frame_count = 0;
		elapsed_time = 0;
	}
}

void	main_render_loop(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	fdf->clicked = fmax(fdf->clicked - fdf->mlx->delta_time, 0);
	if (fdf->draw_fps)
		display_fps(fdf);
	else if (fdf->fps_image)
	{
		mlx_delete_image(fdf->mlx, fdf->fps_image);
		fdf->fps_image = NULL;
	}
	if (fdf->draw_skybox)
		put_skybox(fdf);
	else
		render_background(fdf);
	reset_depth_map(fdf);
	put_mesh(fdf);
	if (fdf->anti_aliasing && fdf->draw_edges)
		adjust_canvas_brightness(1.2, fdf);
}