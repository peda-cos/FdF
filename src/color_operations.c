/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:03:51 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:47:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

uint32_t	get_texture_color(mlx_texture_t *texture, int32_t x, int32_t y)
{
	t_color		color;
	uint32_t	position;

	color.color = 0;
	if (x >= 0 && x < (int32_t)texture->width
		&& y >= 0 && y < (int32_t)texture->height)
	{
		position = (x * 4) + (y * texture->width * 4);
		color.channel[R] = texture->pixels[position + 0];
		color.channel[G] = texture->pixels[position + 1];
		color.channel[B] = texture->pixels[position + 2];
		color.channel[A] = texture->pixels[position + 3];
	}
	return (color.color);
}

uint32_t	get_image_color(mlx_image_t *image, int32_t x, int32_t y)
{
	t_color		color;
	uint32_t	position;

	color.color = 0;
	if (x >= 0 && x < (int32_t)image->width
		&& y >= 0 && y < (int32_t)image->height)
	{
		position = (x * 4) + (y * image->width * 4);
		color.channel[R] = image->pixels[position + 0];
		color.channel[G] = image->pixels[position + 1];
		color.channel[B] = image->pixels[position + 2];
		color.channel[A] = image->pixels[position + 3];
	}
	return (color.color);
}

uint32_t	calculate_fade_color(uint32_t color_start, uint32_t color_end, int32_t steps, int step)
{
	t_color	start;
	t_color	end;

	if (steps < 6)
		return (color_start);
	if (steps > 30)
		return (interpolate_color(color_start, color_end, (double)step / steps));
	start.color = color_start;
	end.color = color_end;
	start.channel[R] += (end.channel[R] - start.channel[R]) / steps * step;
	start.channel[G] += (end.channel[G] - start.channel[G]) / steps * step;
	start.channel[B] += (end.channel[B] - start.channel[B]) / steps * step;
	start.channel[A] += (end.channel[A] - start.channel[A]) / steps * step;
	return (start.color);
}

uint8_t	interpolate_color_channel(uint8_t start, uint8_t end, double factor)
{
	uint8_t	result;

	result = round(start * (1 - factor)) + (end * factor);
	return (result);
}

uint32_t	interpolate_color(uint32_t color_start, uint32_t color_end, double factor)
{
	t_color	start;
	t_color	end;
	t_color	result;

	factor = fmin(factor, 1);
	factor = fmax(factor, 0);
	start.color = color_start;
	end.color = color_end;
	result.channel[R] = interpolate_color_channel(start.channel[R], end.channel[R], factor);
	result.channel[G] = interpolate_color_channel(start.channel[G], end.channel[G], factor);
	result.channel[B] = interpolate_color_channel(start.channel[B], end.channel[B], factor);
	result.channel[A] = interpolate_color_channel(start.channel[A], end.channel[A], factor);
	return (result.color);
}