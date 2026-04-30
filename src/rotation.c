/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(double *y, double *z, double sin_a, double cos_a)
{
	double	prev;

	prev = *y;
	*y = prev * cos_a - *z * sin_a;
	*z = prev * sin_a + *z * cos_a;
}

void	rotate_y(double *x, double *z, double sin_a, double cos_a)
{
	double	prev;

	prev = *x;
	*x = prev * cos_a - *z * sin_a;
	*z = prev * sin_a + *z * cos_a;
}

void	rotate_z(double *x, double *y, double sin_a, double cos_a)
{
	double	prev;

	prev = *x;
	*x = prev * cos_a - *y * sin_a;
	*y = prev * sin_a + *y * cos_a;
}
