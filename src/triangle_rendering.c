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

void	draw_triangle_outlines(t_triangle triangle, t_fdf *fdf)
{
	if (!fdf->draw_faces_with_edges)
		return ;
	triangle.a.color = 0x000000FF;
	triangle.b.color = 0x000000FF;
	triangle.c.color = 0x000000FF;
	triangle.a.depth -= 3;
	triangle.b.depth -= 3;
	triangle.c.depth -= 3;
	draw_line(triangle.a, triangle.b, 1, fdf);
	draw_line(triangle.b, triangle.c, 1, fdf);
	draw_line(triangle.c, triangle.a, 1, fdf);
}

void	calculate_bounding_box(t_triangle *triangle, t_fdf *fdf)
{
	triangle->bounding_box[0].x = ft_imin(
		ft_imax(ft_imin(ft_imin(triangle->a.x, triangle->b.x), triangle->c.x), 0),
		fdf->canvas->width - 1);
	triangle->bounding_box[0].y = ft_imin(
		ft_imax(ft_imin(ft_imin(triangle->a.y, triangle->b.y), triangle->c.y), 0),
		fdf->canvas->height - 1);
	triangle->bounding_box[1].x = ft_imax(
		ft_imin(ft_imax(ft_imax(triangle->a.x, triangle->b.x), triangle->c.x), 
			fdf->canvas->width - 1), 0);
	triangle->bounding_box[1].y = ft_imax(
		ft_imin(ft_imax(ft_imax(triangle->a.y, triangle->b.y), triangle->c.y), 
			fdf->canvas->height - 1), 0);
}

void	render_triangle_pixel(t_pixel pixel, t_triangle triangle, t_fdf *fdf)
{
	triangle.weight_c /= triangle.area;
	triangle.weight_a /= triangle.area;
	triangle.weight_b /= triangle.area;
	pixel.channel[R] = triangle.a.channel[R] * triangle.weight_a +
					   triangle.b.channel[R] * triangle.weight_b +
					   triangle.c.channel[R] * triangle.weight_c;
	pixel.channel[G] = triangle.a.channel[G] * triangle.weight_a +
					   triangle.b.channel[G] * triangle.weight_b +
					   triangle.c.channel[G] * triangle.weight_c;
	pixel.channel[B] = triangle.a.channel[B] * triangle.weight_a +
					   triangle.b.channel[B] * triangle.weight_b +
					   triangle.c.channel[B] * triangle.weight_c;
	pixel.channel[A] = triangle.a.channel[A] * triangle.weight_a +
					   triangle.b.channel[A] * triangle.weight_b +
					   triangle.c.channel[A] * triangle.weight_c;
	pixel.depth = triangle.a.depth * triangle.weight_a +
				  triangle.b.depth * triangle.weight_b +
				  triangle.c.depth * triangle.weight_c;
	put_pixel(fdf->canvas, pixel, 1, fdf);
}

void	render_triangle(t_triangle triangle, t_fdf *fdf)
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
		if (triangle.weight_a >= 0 && triangle.weight_c >= 0)
			triangle.weight_b = calculate_edge_function(triangle.c.pos, triangle.a.pos, pixel.pos);
		if (triangle.weight_c >= 0 && triangle.weight_a >= 0 && triangle.weight_b >= 0)
			render_triangle_pixel(pixel, triangle, fdf);
		pixel.pos.x++;
		if (pixel.pos.x > triangle.bounding_box[1].x)
		{
			pixel.pos.x = triangle.bounding_box[0].x;
			pixel.pos.y++;
		}
	}
	draw_triangle_outlines(triangle, fdf);
}

void	render_face(t_face face, t_fdf *fdf)
{
	t_triangle	triangle1;
	t_triangle	triangle2;

	if (fabs(face.c.z - face.a.z) >= fabs(face.d.z - face.b.z))
	{
		triangle1.a = face.a.pixel;
		triangle1.b = face.b.pixel;
		triangle1.c = face.c.pixel;
		triangle2.a = face.a.pixel;
		triangle2.b = face.c.pixel;
		triangle2.c = face.d.pixel;
	}
	else
	{
		triangle1.a = face.a.pixel;
		triangle1.b = face.b.pixel;
		triangle1.c = face.d.pixel;
		triangle2.a = face.b.pixel;
		triangle2.b = face.c.pixel;
		triangle2.c = face.d.pixel;
	}
	if (triangle1.a.visible && triangle1.b.visible && triangle1.c.visible)
		render_triangle(triangle1, fdf);
	if (triangle2.a.visible && triangle2.b.visible && triangle2.c.visible)
		render_triangle(triangle2, fdf);
}