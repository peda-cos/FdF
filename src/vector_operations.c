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

t_vec3	add_vectors(t_vec3 vector_a, t_vec3 vector_b)
{
	t_vec3	result;

	result.x = vector_a.x + vector_b.x;
	result.y = vector_a.y + vector_b.y;
	result.z = vector_a.z + vector_b.z;
	return (result);
}

void	initialize_skybox_vertices(t_vertex *vertices, t_vec3 start_pos, 
	t_vec3 step1, t_vec3 step2)
{
	t_vec3	current_pos;
	size_t	index;

	current_pos = start_pos;
	vertices[0].position = current_pos;
	vertices[0].pixel.u = 0;
	vertices[0].pixel.v = 0;
	index = 1;
	while (index < 121)
	{
		current_pos = add_vectors(current_pos, step1);
		vertices[index].pixel.u = vertices[index - 1].pixel.u + 0.1;
		vertices[index].pixel.v = vertices[index - 1].pixel.v;
		if (vertices[index].pixel.u > 1)
		{
			current_pos = add_vectors(current_pos, step2);
			vertices[index].pixel.u = 0;
			vertices[index].pixel.v = vertices[index - 1].pixel.v + 0.1;
		}
		vertices[index].position = current_pos;
		index++;
	}
}

void	verify_texture_allocation(mlx_texture_t *texture, char *path, t_fdf *fdf)
{
	if (!texture)
		clean_exit(path, fdf);
}

void	load_skybox_textures(uint8_t skybox_id, t_fdf *fdf)
{
	char	file_path[28];

	delete_skybox_textures(fdf);
	ft_memmove(file_path, "assets/skyboxes/skyX_bk.png\0", 28);
	file_path[19] = skybox_id + '0';
	fdf->skybox.back_texture = mlx_load_png(file_path);
	verify_texture_allocation(fdf->skybox.back_texture, file_path, fdf);
	ft_memmove(file_path + 21, "dn", 2);
	fdf->skybox.down_texture = mlx_load_png(file_path);
	verify_texture_allocation(fdf->skybox.down_texture, file_path, fdf);
	ft_memmove(file_path + 21, "ft", 2);
	fdf->skybox.front_texture = mlx_load_png(file_path);
	verify_texture_allocation(fdf->skybox.front_texture, file_path, fdf);
	ft_memmove(file_path + 21, "lf", 2);
	fdf->skybox.left_texture = mlx_load_png(file_path);
	verify_texture_allocation(fdf->skybox.left_texture, file_path, fdf);
	ft_memmove(file_path + 21, "rt", 2);
	fdf->skybox.right_texture = mlx_load_png(file_path);
	verify_texture_allocation(fdf->skybox.right_texture, file_path, fdf);
	ft_memmove(file_path + 21, "up", 2);
	fdf->skybox.up_texture = mlx_load_png(file_path);
	verify_texture_allocation(fdf->skybox.up_texture, file_path, fdf);
}

void	initialize_skybox(t_fdf *fdf)
{
	load_skybox_textures(1, fdf);
	initialize_skybox_vertices(fdf->skybox.back_vertices,
		(t_vec3){-1, -1, -1}, (t_vec3){0.2, 0, 0}, (t_vec3){-2.2, 0, 0.2});
	initialize_skybox_vertices(fdf->skybox.front_vertices,
		(t_vec3){1, 1, -1}, (t_vec3){-0.2, 0, 0}, (t_vec3){2.2, 0, 0.2});
	initialize_skybox_vertices(fdf->skybox.left_vertices,
		(t_vec3){-1, 1, -1}, (t_vec3){0, -0.2, 0}, (t_vec3){0, 2.2, 0.2});
	initialize_skybox_vertices(fdf->skybox.right_vertices,
		(t_vec3){1, -1, -1}, (t_vec3){0, 0.2, 0}, (t_vec3){0, -2.2, 0.2});
	initialize_skybox_vertices(fdf->skybox.up_vertices,
		(t_vec3){-1, -1, -1}, (t_vec3){0, 0.2, 0}, (t_vec3){0.2, -2.2, 0});
	initialize_skybox_vertices(fdf->skybox.down_vertices,
		(t_vec3){1, -1, 1}, (t_vec3){0, 0.2, 0}, (t_vec3){-0.2, -2.2, 0});
}