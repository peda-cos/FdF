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

void	project_skybox_vertices(t_vertex *vertices, t_fdf *fdf)
{
	size_t		index;
	t_vec3		transformed;

	index = 0;
	while (index < 121)
	{
		transformed.x = vertices[index].x;
		transformed.y = vertices[index].y;
		transformed.x = vertices[index].x * cos(fdf->yaw) + vertices[index].y * -sin(fdf->yaw);
		transformed.y = vertices[index].x * sin(fdf->yaw) + vertices[index].y * cos(fdf->yaw);
		transformed.z = transformed.y;
		transformed.y = transformed.y * cos(fdf->pitch) + vertices[index].z * -sin(fdf->pitch);
		transformed.z = transformed.z * sin(fdf->pitch) + vertices[index].z * cos(fdf->pitch);
		vertices[index].pixel.visible = 1;
		if (transformed.z <= 0)
			vertices[index].pixel.visible = 0;
		vertices[index].pixel.x = round(transformed.x * fdf->focus / -transformed.z);
		vertices[index].pixel.y = round(transformed.y * fdf->focus / -transformed.z);
		vertices[index].pixel.depth = transformed.z;
		vertices[index].pixel.x += fdf->canvas->width / 2;
		vertices[index].pixel.y += fdf->canvas->height / 2;
		index++;
	}
}

void	subdivide_skybox_face(mlx_texture_t *texture, t_vertex *vertices, t_fdf *fdf)
{
	size_t	index;
	t_triangle	triangle;

	index = 12;
	while (index < 121)
	{
		if (index % 11)
		{
			triangle.a = vertices[index - 12].pixel;
			triangle.b = vertices[index - 11].pixel;
			triangle.c = vertices[index - 1].pixel;
			if (triangle.a.visible && triangle.b.visible && triangle.c.visible)
				render_sky_triangle(texture, triangle, fdf);
			triangle.a = vertices[index].pixel;
			triangle.b = vertices[index - 1].pixel;
			triangle.c = vertices[index - 11].pixel;
			if (triangle.a.visible && triangle.b.visible && triangle.c.visible)
				render_sky_triangle(texture, triangle, fdf);
		}
		index++;
	}
}

void	render_skybox(t_fdf *fdf)
{
	project_skybox_vertices(fdf->skybox.back, fdf);
	project_skybox_vertices(fdf->skybox.front, fdf);
	project_skybox_vertices(fdf->skybox.left, fdf);
	project_skybox_vertices(fdf->skybox.right, fdf);
	project_skybox_vertices(fdf->skybox.up, fdf);
	project_skybox_vertices(fdf->skybox.down, fdf);
	subdivide_skybox_face(fdf->skybox.back_texture, fdf->skybox.back, fdf);
	subdivide_skybox_face(fdf->skybox.front_texture, fdf->skybox.front, fdf);
	subdivide_skybox_face(fdf->skybox.left_texture, fdf->skybox.left, fdf);
	subdivide_skybox_face(fdf->skybox.right_texture, fdf->skybox.right, fdf);
	subdivide_skybox_face(fdf->skybox.up_texture, fdf->skybox.up, fdf);
	subdivide_skybox_face(fdf->skybox.down_texture, fdf->skybox.down, fdf);
}