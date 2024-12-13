/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 by peda-cos            #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	toggle_arot(t_auto *state)
{
	if (*state == AUTO_STOP)
		*state = AUTO_CW;
	else if (*state == AUTO_CW)
		*state = AUTO_CCW;
	else
		*state = AUTO_STOP;
}

static void	reset_cam_top(t_mlx *m)
{
	m->cam.x_ang = 0;
	m->cam.y_ang = 0;
	m->cam.z_ang = 0;
	m->cam.proj = PROJ_TOP;
}

static void	auto_rot_key(mlx_key_data_t kd, t_mlx *m)
{
	if (kd.key == MLX_KEY_Z)
		toggle_arot(&m->cam.arot_x);
	if (kd.key == MLX_KEY_X)
		toggle_arot(&m->cam.arot_y);
	if (kd.key == MLX_KEY_C)
		toggle_arot(&m->cam.arot_z);
	if (kd.key == MLX_KEY_V)
	{
		m->cam.arot_x = AUTO_STOP;
		m->cam.arot_y = AUTO_STOP;
		m->cam.arot_z = AUTO_STOP;
	}
}

void	handle_key(mlx_key_data_t kd, void *prm)
{
	t_mlx	*m;

	m = (t_mlx *)prm;
	if (kd.action == MLX_PRESS)
	{
		if (kd.key == MLX_KEY_ESCAPE)
			cleanup_exit(m, 0);
		if (kd.key == MLX_KEY_0)
		{
			if (m->cam.line_type == 0)
				m->cam.line_type = 1;
			else
				m->cam.line_type = 0;
		}
		if (kd.key == MLX_KEY_R || kd.key == MLX_KEY_F1
			|| kd.key == MLX_KEY_F2)
		{
			init_cam(m);
			if (kd.key == MLX_KEY_F2)
				reset_cam_top(m);
		}
		auto_rot_key(kd, m);
	}
}
