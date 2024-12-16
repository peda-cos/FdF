/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+
	+#+         */
/*                                                +#+#+#+#+#+
	+#+            */
/*   Created: 2024/11/15 20:22:13 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:15:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static void	initialize_mlx(t_mlx *mlx_instance);

int	main(int argc, char *argv[])
{
	t_mlx mlx_instance;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Incorrect number of arguments.\n", 2);
		return (EXIT_FAILURE);
	}
	mlx_instance.map = malloc(sizeof(t_map));
	if (!mlx_instance.map)
		return (EXIT_FAILURE);
	if (!parse_map(argv[1], mlx_instance.map))
		return (safe_exit_on_error(mlx_instance.map, NULL, -1, EXIT_FAILURE));
	initialize_mlx(&mlx_instance);
	if (mlx_image_to_window(mlx_instance.mlx, mlx_instance.img, 0, 0) < 0)
		cleanup_exit(&mlx_instance, EXIT_FAILURE);
	run_fdf(&mlx_instance, mlx_instance.map);
	mlx_key_hook(mlx_instance.mlx, handle_key_event, &mlx_instance);
	mlx_loop(mlx_instance.mlx);
	cleanup_exit(&mlx_instance, EXIT_SUCCESS);
}

static void	initialize_mlx(t_mlx *mlx_instance)
{
	mlx_instance->mlx = mlx_init(g_resolution_x, g_resolution_y, "FDF Viewer",
			true);
	if (!mlx_instance->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MLX42.\n", 2);
		safe_exit_on_error(mlx_instance->map, NULL, -1, EXIT_FAILURE);
	}
	mlx_instance->img = mlx_new_image(mlx_instance->mlx, g_resolution_x,
			g_resolution_y);
	if (!mlx_instance->img)
		cleanup_exit(mlx_instance, EXIT_FAILURE);
}
