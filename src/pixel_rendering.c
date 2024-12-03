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

void	draw_large_pixel(mlx_image_t *image, t_pixel pixel, uint8_t size, t_fdf *fdf)
{
	t_ivec2	index;
	t_ivec2	center;
	double	radius;

	index = (t_ivec2){0, 0};
	center = pixel.pos;
	radius = (double)size / 2;
	pixel.x -= size / 2 + 1;
	pixel.y -= size / 2 + 1;
	while (index.y < size + 2)
	{
		if (get_length(pixel.pos, center) <= radius)
			put_pixel(image, pixel, 1, fdf);
		pixel.x++;
		index.x++;
		if (index.x == size + 2)
		{
			pixel.y++;
			index.y++;
			pixel.x -= size + 2;
			index.x = 0;
		}
	}
}

void	store_depth(t_pixel pixel, t_fdf *fdf)
{
	uint32_t	position;
	float		depth_value;

	position = pixel.x * 4 + pixel.y * fdf->depth_map->width * 4;
	depth_value = (float)pixel.depth;
	ft_memmove(&fdf->depth_map->pixels[position], &depth_value, 4);
}

float	get_depth(t_pixel pixel, t_fdf *fdf)
{
	uint32_t	position;
	float		depth_value;

	position = pixel.x * 4 + pixel.y * fdf->depth_map->width * 4;
	ft_memmove(&depth_value, &fdf->depth_map->pixels[position], 4);
	return (depth_value);
}

void	draw_anti_aliased_pixel(mlx_image_t *image, t_pixel pixel, t_fdf *fdf)
{
	t_pixel	existing_pixel;

	if (pixel.channel[A] && pixel.x >= 0 && pixel.x < (int)image->width
		&& pixel.y >= 0 && pixel.y < (int)image->height)
	{
		existing_pixel.pos = pixel.pos;
		existing_pixel.color = sample_image(fdf->canvas, pixel.x, pixel.y);
		existing_pixel.depth = get_depth(pixel, fdf);
		if (pixel.depth > existing_pixel.depth)
		{
			mlx_put_pixel(fdf->canvas, pixel.x, pixel.y, 0);
			mlx_put_pixel(fdf->depth_map, pixel.x, pixel.y, 0x7f96184b);
			draw_anti_aliased_pixel(fdf->canvas, pixel, fdf);
			draw_anti_aliased_pixel(fdf->canvas, existing_pixel, fdf);
			return ;
		}
		if (existing_pixel.channel[A])
			pixel.color = lerp_color(existing_pixel.color, pixel.color,
					(double)pixel.channel[A] / existing_pixel.channel[A] * 1.2);
		pixel.channel[A] = ft_imax(pixel.channel[A], existing_pixel.channel[A]);
		mlx_put_pixel(fdf->canvas, pixel.x, pixel.y, pixel.color);
		store_depth(pixel, fdf);
	}
}

void	draw_pixel(mlx_image_t *image, t_pixel pixel, uint8_t size, t_fdf *fdf)
{
	float	existing_depth;

	if (!pixel.channel[A])
		return ;
	if (size > 1)
		draw_large_pixel(image, pixel, size, fdf);
	else if (pixel.x >= 0 && pixel.x < (int)image->width
		&& pixel.y >= 0 && pixel.y < (int)image->height)
	{
		existing_depth = get_depth(pixel, fdf);
		if (pixel.depth > existing_depth)
			return ;
		mlx_put_pixel(image, pixel.x, pixel.y, pixel.color);
		store_depth(pixel, fdf);
	}
}