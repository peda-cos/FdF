/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:22:22 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:22:23 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

unsigned int calc_ip(long s, long e, long n, long mx)
{
	double r;

	if (mx == 0)
		return (s);
	r = (double)n / (double)mx;
	return ((unsigned int)((unsigned long)(s + r * (e - s) + 0.5)));
}

int calc_dist(t_point p1, t_point p2)
{
	int r;

	r = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	return (r);
}
