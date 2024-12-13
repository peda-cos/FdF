/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:20:59 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/12 20:21:58 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void calc_scr(t_map *mp, t_screen *s);
static void calc_coord(t_map *mp, t_screen *s);

void run_fdf(t_mlx *m, t_map *mp)
{
	calc_scr(mp, &m->s);
	calc_coord(mp, &m->s);
	draw_grid(m, mp);
}

void skip_line(int fd)
{
	char    *l;

	l = get_next_line(fd);
	while (l)
	{
		free(l);
		l = get_next_line(fd);
	}
}

static void calc_scr(t_map *mp, t_screen *s)
{
	int lw;

	lw = 0;
	if (mp->w < mp->h)
		s->half_tiles = (mp->w * 2 + (mp->h - mp->w));
	else
		s->half_tiles = (mp->h * 2 + (mp->w - mp->h));
	if (g_res_x > g_res_y)
	{
		s->half_tile_w = g_res_y / s->half_tiles;
		lw = (g_res_x - g_res_y) / 2;
	}
	else
		s->half_tile_w = g_res_x / s->half_tiles;
	if (s->half_tile_w < 2)
		s->half_tile_w = 2;
	s->half_tile_h = s->half_tile_w * tan(M_PI / 6);
	s->start_x = mp->h * s->half_tile_w + lw;
	s->mar_x = (g_res_x - s->half_tiles * s->half_tile_w) / 2;
	s->mar_y = (g_res_y - s->half_tiles * s->half_tile_h) / 2;
}

static void calc_coord(t_map *mp, t_screen *s)
{
	int     h;
	int     w;
	int     hm;
	t_point *p;

	h = 0;
	hm = s->half_tile_h / 2;
	if (hm < 1)
		hm = 1;
	while (h < mp->h)
	{
		w = 0;
		while (w < mp->w)
		{
			p = &mp->grid[h][w];
			p->x = s->start_x + (w - h) * (s->half_tile_w);
			p->y = s->mar_y + ((w + h) * (s->half_tile_h))
				- p->value * hm;
			set_pt_clr(p, *mp);
			w++;
		}
		h++;
	}
}

void draw_grid(t_mlx *m, t_map *mp)
{
	int         h;
	int         w;
	mlx_image_t *im;

	im = m->img1;
	fill_bg(m, g_bg_c);
	h = 0;
	while (h < mp->h)
	{
		w = 0;
		while (w < mp->w)
		{
			if (w != mp->w - 1)
				draw_ln(im, mp->grid[h][w], mp->grid[h][w + 1]);
			if (h != mp->h - 1)
				draw_ln(im, mp->grid[h][w], mp->grid[h + 1][w]);
			w++;
		}
		h++;
	}
}
