/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:30:10 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 01:30:23 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void draw_header(t_mlx *m, int *x, int *y, int dist)
{
	mlx_put_string(m->mlx, "______  ______  ______ ", *x, *y);
	*y += dist;
	mlx_put_string(m->mlx, "|  ___| |  _  \\ |  ___|", *x, *y);
	*y += dist;
	mlx_put_string(m->mlx, "| |_    | | | | | |_   ", *x, *y);
	*y += dist;
	mlx_put_string(m->mlx, "|  _|   | | | | |  _|  ", *x, *y);
	*y += dist;
	mlx_put_string(m->mlx, "| |     | |/ /  | |    ", *x, *y);
	*y += dist;
	mlx_put_string(m->mlx, "\\_|     |___/   \\_|    ", *x, *y);
	*y += dist;
	mlx_put_string(m->mlx, "------------------------ ", *x, *y);
	*y += dist;
}

static void body_1(t_mlx *m, int *x, int *y, int dist)
{
	mlx_put_string(m->mlx, "Move Up       == 'I'", *x, *y += dist);
	mlx_put_string(m->mlx, "Move Down     == 'K'", *x, *y += dist);
	mlx_put_string(m->mlx, "Move Left     == 'J'", *x, *y += dist);
	mlx_put_string(m->mlx, "Move Right    == 'L'", *x, *y += dist);
	mlx_put_string(m->mlx, "Rotate +X     == 'W'", *x, *y += dist);
	mlx_put_string(m->mlx, "Rotate -X     == 'S'", *x, *y += dist);
	mlx_put_string(m->mlx, "Rotate +Y     == 'E'", *x, *y += dist);
	mlx_put_string(m->mlx, "Rotate -Y     == 'Q'", *x, *y += dist);
	mlx_put_string(m->mlx, "Rotate +Z     == 'D'", *x, *y += dist);
	mlx_put_string(m->mlx, "Rotate -Z     == 'A'", *x, *y += dist);
	mlx_put_string(m->mlx, "Increase Z    == 'UP'", *x, *y += dist);
	mlx_put_string(m->mlx, "Decrease Z    == 'DOWN'", *x, *y += dist);
}

static void body_2(t_mlx *m, int *x, int *y, int dist)
{
	mlx_put_string(m->mlx, "Zoom In       == '='", *x, *y += dist);
	mlx_put_string(m->mlx, "Zoom Out      == '-'", *x, *y += dist);
	mlx_put_string(m->mlx, "Isometric     == 'F1'", *x, *y += dist);
	mlx_put_string(m->mlx, "Top-Down      == 'F2'", *x, *y += dist);
	mlx_put_string(m->mlx, "Reset         == 'R'", *x, *y += dist);
	mlx_put_string(m->mlx, "Change Line   == '0'", *x, *y += dist);
}

static void body_3(t_mlx *m, int *x, int *y, int dist)
{
	mlx_put_string(m->mlx, "Auto Rotate:", *x, *y += dist);
	mlx_put_string(m->mlx, " - Rotate X   == 'z'", *x, *y += dist);
	mlx_put_string(m->mlx, " - Rotate Y   == 'x'", *x, *y += dist);
	mlx_put_string(m->mlx, " - Rotate Z   == 'c'", *x, *y += dist);
	mlx_put_string(m->mlx, " - Stop       == 'v'", *x, *y += dist);
	mlx_put_string(m->mlx, "Close         == 'ESC'", *x, *y += dist);
	mlx_put_string(m->mlx, "------------------------ ", *x, *y += dist);
}

void show_menu(t_mlx *m)
{
	int start_y;
	int start_x;
	int line_dist;

	start_x = 7;
	start_y = 0;
	line_dist = 22;
	draw_header(m, &start_x, &start_y, line_dist);
	body_1(m, &start_x, &start_y, line_dist);
	body_2(m, &start_x, &start_y, line_dist);
	body_3(m, &start_x, &start_y, line_dist);
}
