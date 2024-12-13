/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:22:05 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:22:07 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void handle_key(mlx_key_data_t kd, void *prm)
{
	t_mlx *m;

	m = (t_mlx *)prm;
	if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		cleanup_exit(m, EXIT_SUCCESS);
	else if (kd.key == MLX_KEY_UP && kd.action == MLX_PRESS)
		shift_map(m, UP);
	else if (kd.key == MLX_KEY_DOWN && kd.action == MLX_PRESS)
		shift_map(m, DOWN);
	else if (kd.key == MLX_KEY_LEFT && kd.action == MLX_PRESS)
		shift_map(m, LEFT);
	else if (kd.key == MLX_KEY_RIGHT && kd.action == MLX_PRESS)
		shift_map(m, RIGHT);
	else if (kd.key == MLX_KEY_W && kd.action == MLX_PRESS)
		zoom_inc(m);
	else if (kd.key == MLX_KEY_S && kd.action == MLX_PRESS)
		zoom_dec(m);
	draw_grid(m, m->map);
}
