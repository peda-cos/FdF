/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:20:42 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:20:43 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void init_br(t_br *b, t_point p1, t_point p2);
static int  clip_ln(t_point *p1, t_point *p2);
static void draw_bresen(mlx_image_t *img, t_point p1, t_point p2, t_br b);

void    draw_ln(mlx_image_t *img, t_point p1, t_point p2)
{
	t_br b;

	if (!clip_ln(&p1, &p2))
		return ;
	init_br(&b, p1, p2);
	draw_bresen(img, p1, p2, b);
}

static void draw_bresen(mlx_image_t *img, t_point p1, t_point p2, t_br b)
{
	while (1)
	{
		if (p1.x < g_res_x && p1.y < g_res_y && p1.x > 0 && p1.y > 0)
			mlx_put_pixel(img, p1.x, p1.y, b.color);
		else if ((p1.x > g_res_x && b.ddx > 0) ||
			(p1.y > g_res_y && b.ddy > 0) ||
			(p1.x < 0 && b.ddx < 0) ||
			(p1.y < 0 && b.ddy < 0))
			return ;
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		b.e2 = b.err * 2;
		if (b.e2 > -b.dy)
		{
			b.err -= b.dy;
			p1.x += b.sx;
		}
		if (b.e2 < b.dx)
		{
			b.err += b.dx;
			p1.y += b.sy;
		}
		b.color = calc_grad(p1, p2, b.t_l);
	}
}

static int clip_ln(t_point *p1, t_point *p2)
{
	if (p1->x < 0)
	{
		if (p2->x != p1->x)
			p1->y += ((p2->y - p1->y) * (-p1->x)) / (p2->x - p1->x);
		p1->x = 0;
	}
	else if (p1->x > g_res_x)
	{
		if (p2->x != p1->x)
			p1->y += ((p2->y - p1->y) * (g_res_x - p1->x))
				/ (p2->x - p1->x);
		p1->x = g_res_x;
	}
	if (p1->y < 0)
	{
		if (p2->y != p1->y)
			p1->x += (p2->x - p1->x) * (-p1->y) / (p2->y - p1->y);
		p1->y = 0;
	}
	else if (p1->y > g_res_y)
	{
		if (p2->y != p1->y)
			p1->x += (p2->x - p1->x) * (g_res_y - p1->y)
				/ (p2->y - p1->y);
		p1->y = g_res_y;
	}
	return (p1->x >= 0 && p1->x <= g_res_x && p1->y >= 0 && p1->y <= g_res_y);
}

static void init_br(t_br *b, t_point p1, t_point p2)
{
	b->dx = labs((long)p2.x - (long)p1.x);
	b->ddx = (long)p2.x - (long)p1.x;
	b->dy = labs((long)p2.y - (long)p1.y);
	b->ddy = (long)p2.y - (long)p1.y;
	if (p1.x < p2.x)
		b->sx = 1;
	else
		b->sx = -1;
	if (p1.y < p2.y)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx - b->dy;
	b->t_l = calc_dist(p1, p2);
	b->color = calc_grad(p1, p2, b->t_l);
}
