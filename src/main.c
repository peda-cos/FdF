/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:33:37 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:34:26 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image;
	int32_t		image_id;

	if (argc != 2)
	{
		perror("Wrong number of arguments.");
		return (0);
	}
	mlx_ptr = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx_ptr)
		print_error_and_exit();
	image = mlx_new_image(mlx_ptr, 1920, 1080);
	if (handle_map(mlx_ptr, image, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	image_id = mlx_image_to_window(mlx_ptr, image, 0, 0);
	if (!image || image_id < 0)
		print_error_and_exit();
	mlx_loop_hook(mlx_ptr, handle_mlx_events, mlx_ptr);
	mlx_loop(mlx_ptr);
	mlx_delete_image(mlx_ptr, image);
	mlx_terminate(mlx_ptr);
	return (EXIT_SUCCESS);
}

void	handle_mlx_events(void *param)
{
	mlx_t	*mlx_ptr;

	mlx_ptr = (mlx_t *)param;
	if (mlx_is_key_down(mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(mlx_ptr);
}

void	print_error_and_exit(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
