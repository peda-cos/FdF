/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	alloc_projected(t_fdf *fdf)
{
	int	i;

	fdf->projected = malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->projected)
		return (-1);
	i = 0;
	while (i < fdf->map.height)
	{
		fdf->projected[i] = malloc(sizeof(t_point) * fdf->map.width);
		if (!fdf->projected[i])
		{
			while (--i >= 0)
				free(fdf->projected[i]);
			free(fdf->projected);
			fdf->projected = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	run_fdf(char *map_file)
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(t_fdf));
	if (parse_map(map_file, &fdf.map) == -1)
		exit_error("Error: invalid map\n", NULL);
	assign_default_colors(&fdf.map);
	if (alloc_projected(&fdf) == -1)
		exit_error("Error: alloc failed\n", &fdf);
	if (init_fdf(&fdf) == -1)
		exit_error("Error: MLX init failed\n", &fdf);
	init_camera(&fdf.cam, &fdf.map);
	render(&fdf);
	setup_hooks(&fdf);
	mlx_loop(fdf.mlx);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2);
		return (1);
	}
	run_fdf(argv[1]);
	return (0);
}
