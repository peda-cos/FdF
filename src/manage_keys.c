/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 by peda-cos            #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	arot_off(t_mlx *m)
{
	return (m->cam.arot_x == AUTO_STOP && m->cam.arot_y == AUTO_STOP
		&& m->cam.arot_z == AUTO_STOP);
}

static void	rotate_keys(t_mlx *m)
{
	if (m->cam.proj != PROJ_TOP)
	{
		if ((mlx_is_key_down(m->mlx, MLX_KEY_W) && arot_off(m))
			|| m->cam.arot_x == AUTO_CW)
			m->cam.x_ang += 1;
		if ((mlx_is_key_down(m->mlx, MLX_KEY_S) && arot_off(m))
			|| m->cam.arot_x == AUTO_CCW)
			m->cam.x_ang -= 1;
		if ((mlx_is_key_down(m->mlx, MLX_KEY_E) && arot_off(m))
			|| m->cam.arot_y == AUTO_CW)
			m->cam.y_ang += 1;
		if ((mlx_is_key_down(m->mlx, MLX_KEY_Q) && arot_off(m))
			|| m->cam.arot_y == AUTO_CCW)
			m->cam.y_ang -= 1;
	}
	if ((mlx_is_key_down(m->mlx, MLX_KEY_D) && arot_off(m))
		|| m->cam.arot_z == AUTO_CW)
		m->cam.z_ang += 1;
	if ((mlx_is_key_down(m->mlx, MLX_KEY_A) && arot_off(m))
		|| m->cam.arot_z == AUTO_CCW)
		m->cam.z_ang -= 1;
}

static void	scale_keys(t_mlx *m)
{
	if (mlx_is_key_down(m->mlx, MLX_KEY_UP) && m->cam.z_fac < 20)
		m->cam.z_fac += 0.2;
	if (mlx_is_key_down(m->mlx, MLX_KEY_DOWN) && m->cam.z_fac > -20)
		m->cam.z_fac -= 0.2;
	if (mlx_is_key_down(m->mlx, MLX_KEY_EQUAL))
		m->cam.scl += 0.01;
	if (mlx_is_key_down(m->mlx, MLX_KEY_MINUS) && m->cam.scl > 0.01)
		m->cam.scl -= 0.01;
}

static void	move_keys(t_mlx *m)
{
	if (mlx_is_key_down(m->mlx, MLX_KEY_I))
		m->cam.y_off -= g_mv_amt;
	if (mlx_is_key_down(m->mlx, MLX_KEY_K))
		m->cam.y_off += g_mv_amt;
	if (mlx_is_key_down(m->mlx, MLX_KEY_J))
		m->cam.x_off -= g_mv_amt;
	if (mlx_is_key_down(m->mlx, MLX_KEY_L))
		m->cam.x_off += g_mv_amt;
}

void	manage_keys(t_mlx *m)
{
	rotate_keys(m);
	scale_keys(m);
	move_keys(m);
}
