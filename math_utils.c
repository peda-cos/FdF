/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+      */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+            */
/*   Created: 2024/11/15 20:22:22 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/16 21:15:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


unsigned int	calculate_interpolation(long start, long end, long numerator,
		long max)
{
	double ratio;

	if (max == 0)
		return (start);
	ratio = (double)numerator / (double)max;
	return ((unsigned int)((unsigned long)(start + ratio * (end - start)
				+ 0.5)));
}

int	calculate_distance(t_point point1, t_point point2)
{
	return ((int)sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y,
				2)));
}
