/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 by peda-cos            #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	apply_transformations(t_mlx *m)
{
	manage_keys(m);
	fill_bg(m, g_bg_c);
	draw_grid(m, m->map);
}

void	frame_hook(void *param)
{
	t_mlx	*m;

	m = (t_mlx *)param;
	apply_transformations(m);
}
