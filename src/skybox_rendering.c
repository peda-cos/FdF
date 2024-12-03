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

static void	calculate_bounding_box(t_triangle *triangle, t_fdf *fdf)
{
	triangle->bounding_box[0].x = ft_imin(
		ft_imax(ft_imin(ft_imin(triangle->a.x, triangle->b.x), triangle->c.x), 0),
		fdf->background->width - 1);
	triangle->bounding_box[0].y = ft_imin(
		ft_imax(ft_imin(ft_imin(triangle->a.y, triangle->b.y), triangle->c.y), 0),
		fdf->background->height - 1);
	triangle->bounding_box[1].x = ft_imax(
		ft_imin(ft_imax(ft_imax(triangle->a.x, triangle->b.x), triangle->c.x),
			fdf->background->width - 1), 0);
	triangle->bounding_box[1].y = ft_imax(
		ft_imin(ft_imax(ft_imax(triangle->a.y, triangle->b.y), triangle->c.y),
			fdf->background->height - 1), 0);
}

void	render_sky_pixel(mlx_texture_t *texture, t_pixel pixel, t_triangle triangle, t_fdf *fdf)
{
	double	u;
	double	v;

	triangle.weight_c /= triangle.area;
	triangle.weight_a /= triangle.area;
	triangle.weight_b /= triangle.area;
	u = triangle.a.u + (triangle.b.u - triangle.a.u) * triangle.weight_b;
	v = triangle.a.v + (triangle.c.v - triangle.a.v) * triangle.weight_c;
	pixel.color = sample_texture(texture, (texture->width - 1) * u,
			(texture->height - 1) * v);
	mlx_put_pixel(fdf->background, pixel.x, pixel.y, pixel.color);
}

void	render_sky_triangle(mlx_texture_t *texture, t_triangle triangle, t_fdf *fdf)
{
	t_pixel	pixel;

	triangle.area = calculate_edge_function(triangle.a.pos, triangle.b.pos, triangle.c.pos);
	if (triangle.area <= 0)
		return ;
	calculate_bounding_box(&triangle, fdf);
	pixel.pos = triangle.bounding_box[0];
	while (pixel.pos.y <= triangle.bounding_box[1].y)
	{
		triangle.weight_c = calculate_edge_function(triangle.a.pos, triangle.b.pos, pixel.pos);
		if (triangle.weight_c >= 0)
			triangle.weight_a = calculate_edge_function(triangle.b.pos, triangle.c.pos, pixel.pos);
		if (triangle.weight_c >= 0 && triangle.weight_a >= 0)
			triangle.weight_b = calculate_edge_function(triangle.c.pos, triangle.a.pos, pixel.pos);
		if (triangle.weight_c >= 0 && triangle.weight_a >= 0 && triangle.weight_b >= 0)
			render_sky_pixel(texture, pixel, triangle, fdf);
		pixel.pos.x++;
		if (pixel.pos.x > triangle.bounding_box[1].x)
		{
			pixel.pos.x = triangle.bounding_box[0].x;
			pixel.pos.y++;
		}
	}
}