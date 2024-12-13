/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:20:59 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	calc_scr(t_map *mp, t_screen *s)
{
	int	lw;

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
	s->half_tile_h = s->half_tile_w * tan(g_pi / 6);
	s->start_x = mp->h * s->half_tile_w + lw;
	s->mar_x = (g_res_x - s->half_tiles * s->half_tile_w) / 2;
	s->mar_y = (g_res_y - s->half_tiles * s->half_tile_h) / 2;
}

static void	calc_coord(t_map *mp, t_screen *s)
{
	int		h;
	int		w;
	int		hm;
	t_point	*p;

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

void	run_fdf(t_mlx *m, t_map *mp)
{
	calc_scr(mp, &m->s);
	calc_coord(mp, &m->s);
	draw_grid(m, mp);
}

void	skip_line(int fd)
{
	char	*l;

	l = get_next_line(fd);
	while (l)
	{
		free(l);
		l = get_next_line(fd);
	}
}
