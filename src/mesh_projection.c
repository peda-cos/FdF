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

void	calculate_directions(t_fdf *fdf)
{
	t_vec3	vec;

	vec = (t_vec3){1, 0, 0};
	vec.x = fdf->mesh_scale * cos(fdf->yaw);
	vec.y = fdf->mesh_scale * sin(fdf->yaw);
	vec.z = 0;
	fdf->x_dir.x = vec.x;
	fdf->x_dir.y = vec.y * cos(fdf->pitch) + vec.z * -sin(fdf->pitch);
	fdf->x_dir.z = vec.y * sin(fdf->pitch) + vec.z * cos(fdf->pitch);

	vec = (t_vec3){0, 1, 0};
	vec.x = fdf->mesh_scale * -sin(fdf->yaw);
	vec.y = fdf->mesh_scale * cos(fdf->yaw);
	vec.z = 0;
	fdf->y_dir.x = vec.x;
	fdf->y_dir.y = vec.y * cos(fdf->pitch) + vec.z * -sin(fdf->pitch);
	fdf->y_dir.z = vec.y * sin(fdf->pitch) + vec.z * cos(fdf->pitch);

	vec = (t_vec3){0, 0, 1};
	vec.x = 0;
	vec.y = 0;
	vec.z = fdf->height_scale * fdf->mesh_scale;
	fdf->z_dir.x = vec.x;
	fdf->z_dir.y = vec.y * cos(fdf->pitch) + vec.z * -sin(fdf->pitch);
	fdf->z_dir.z = vec.y * sin(fdf->pitch) + vec.z * cos(fdf->pitch);
}

t_vec3	transform_object_to_world(t_vec3 object, t_fdf *fdf)
{
	t_vec3	world;

	world.x = object.x * fdf->x_dir.x + object.y * fdf->y_dir.x + object.z * fdf->z_dir.x;
	world.y = object.x * fdf->x_dir.y + object.y * fdf->y_dir.y + object.z * fdf->z_dir.y;
	world.z = object.x * fdf->x_dir.z + object.y * fdf->y_dir.z + object.z * fdf->z_dir.z;
	world.x += round(fdf->mesh_position.x);
	world.y += round(fdf->mesh_position.y);
	return (world);
}

void	project_vertices_to_canvas(t_fdf *fdf)
{
	uint32_t	index;
	t_vec3		position;

	index = 0;
	calculate_directions(fdf);
	while (index < fdf->vertex_count)
	{
		position = transform_object_to_world(fdf->vertices[index].position, fdf);
		fdf->vertices[index].pixel.visible = 1;
		fdf->vertices[index].pixel.depth = fdf->camera_height - position.z;

		if (fdf->orthographic)
			fdf->vertices[index].pixel.screen_position = 
				(t_ivec2){round(position.x), round(position.y)};
		else
		{
			if (fdf->vertices[index].pixel.depth <= 0.1)
				fdf->vertices[index].pixel.visible = 0;
			fdf->vertices[index].pixel.x = round(position.x * fdf->focus / fdf->vertices[index].pixel.depth);
			fdf->vertices[index].pixel.y = round(position.y * fdf->focus / fdf->vertices[index].pixel.depth);
		}
		fdf->vertices[index].pixel.x += fdf->canvas->width / 2;
		fdf->vertices[index].pixel.y += fdf->canvas->height / 2;
		index++;
	}
}