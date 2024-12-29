/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:02:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/28 21:36:41 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (1);
	fdf.map = initialize_map();
	load_map(argv[1], fdf.map);
	fdf.mlx_instance = mlx_init(WIDTH, HEIGHT, "FdF - peda-cos", true);
	if (!fdf.mlx_instance)
		exit(EXIT_FAILURE);
	fdf.image = mlx_new_image(fdf.mlx_instance, WIDTH, HEIGHT);
	if (!fdf.image)
		exit(EXIT_FAILURE);
	initialize_camera(&fdf);
	render_map(&fdf);
	set_hooks(&fdf);
	mlx_loop(fdf.mlx_instance);
	mlx_terminate(fdf.mlx_instance);
	free(fdf.camera);
	free_map(fdf.map);
	return (0);
}
