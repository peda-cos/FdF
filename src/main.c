/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:22:13 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:22:14 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void init_mlx_app(t_mlx *m);

int main(int ac, char *av[])
{
	t_mlx m;

	if (ac != 2)
	{
		ft_putstr_fd("Incorrect number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	m.map = malloc(sizeof(t_map));
	if (!m.map)
		exit(EXIT_FAILURE);
	if (!parse_map(av[1], m.map))
	{
		ft_putstr_fd("Map error.\n", 2);
		if (m.map)
			free(m.map);
		exit(EXIT_FAILURE);
	}
	init_mlx_app(&m);
	if (mlx_image_to_window(m.mlx, m.img1, 0, 0) < 0)
		cleanup_exit(&m, EXIT_FAILURE);
	run_fdf(&m, m.map);
	mlx_key_hook(m.mlx, &handle_key, &m);
	mlx_loop(m.mlx);
	cleanup_exit(&m, EXIT_SUCCESS);
}

static void init_mlx_app(t_mlx *m)
{
	m->mlx = mlx_init(g_res_x, g_res_y, "fdf", 1);
	if (!m->mlx)
		exit(EXIT_FAILURE);
	m->img1 = mlx_new_image(m->mlx, g_res_x, g_res_y);
	if (!m->img1)
		cleanup_exit(m, EXIT_FAILURE);
}
