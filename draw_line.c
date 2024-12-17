/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+            */
/*   Created: 2024/11/15 20:20:42 by peda-cos          #+#    #+#              */
/*   Updated: 2024/12/17 00:40:00 by peda-cos         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static void	draw_bresenham_line(mlx_image_t *image, t_point p1, t_point p2,
		t_bresenham bres)
{
	while (1)
	{
		if (p1.x >= 0 && p1.x < g_resolution_x && p1.y >= 0
			&& p1.y < g_resolution_y)
			mlx_put_pixel(image, p1.x, p1.y, bres.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		bres.error2 = bres.error * 2;
		if (bres.error2 > -bres.dy)
		{
			bres.error -= bres.dy;
			p1.x += bres.step_x;
		}
		if (bres.error2 < bres.dx)
		{
			bres.error += bres.dx;
			p1.y += bres.step_y;
		}
		bres.color = calculate_gradient(p1, p2, bres.total_length);
	}
}

static int	clip_line(t_point *p1, t_point *p2)
{
	if (p1->x < 0 || p1->x > g_resolution_x || p1->y < 0
		|| p1->y > g_resolution_y)
		return (0);
	if (p2->x < 0 || p2->x > g_resolution_x || p2->y < 0
		|| p2->y > g_resolution_y)
		return (0);
	return (1);
}

static void	init_bresenham(t_bresenham *bres, t_point p1, t_point p2)
{
	bres->dx = labs(p2.x - p1.x);
	bres->dy = labs(p2.y - p1.y);
	bres->step_x = (p1.x < p2.x) ? 1 : -1;
	bres->step_y = (p1.y < p2.y) ? 1 : -1;
	bres->error = bres->dx - bres->dy;
	bres->total_length = calculate_distance(p1, p2);
	bres->color = calculate_gradient(p1, p2, bres->total_length);
}

void	draw_line(mlx_image_t *image, t_point p1, t_point p2)
{
	t_bresenham bres;

	if (!clip_line(&p1, &p2))
		return ;
	init_bresenham(&bres, p1, p2);
	draw_bresenham_line(image, p1, p2, bres);
}
