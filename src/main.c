/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:46:06 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/24 14:46:07 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	initialize(t_data *data, int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map_file>\n", 24);
		exit(EXIT_FAILURE);
	}
	data->map = parse_map(argv[1]);
	data->mlx = mlx_init(800, 600, "FdF", true);
	if (!data->mlx)
		error_exit("MLX42 initialization failed");
	data->window = data->mlx->window;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = safe_malloc(sizeof(t_data));
	initialize(data, argc, argv);
	render_map(data->map, data->mlx, data->window);
	setup_hooks(data->mlx, data);
	mlx_loop(data->mlx);
	cleanup(data);
	return (0);
}

void	cleanup(t_data *data)
{
	mlx_terminate(data->mlx);
	free_map(data->map);
	free(data);
}
