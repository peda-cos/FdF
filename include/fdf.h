/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line_bonus.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define ISO 0
# define PARALLEL 1

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		z_min;
	int		z_max;
	int		**z_values;
	int		**colors;
}	t_map;

typedef struct s_camera
{
	double	zoom;
	double	z_scale;
	double	x_rot;
	double	y_rot;
	double	z_rot;
	int		offset_x;
	int		offset_y;
	int		projection;
}	t_camera;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_camera	cam;
}	t_fdf;

int		parse_map(char *filename, t_map *map);

int		parse_hex(char *str);
void	parse_token(char *token, int *z, int *color);
void	free_split(char **arr);
void	exit_error(char *msg, t_fdf *fdf);

int		init_fdf(t_fdf *fdf);
void	init_camera(t_camera *cam, t_map *map);

void	free_map(t_map *map);
void	cleanup_fdf(t_fdf *fdf);
int		close_handler(t_fdf *fdf);

t_point	project_point(int x, int y, t_fdf *fdf);

int		interpolate_color(int c1, int c2, double t);
void	assign_default_colors(t_map *map);
double	line_progress(int current, int start, int end);

void	draw_line(t_img *img, t_point p0, t_point p1);

void	render(t_fdf *fdf);

void	setup_hooks(t_fdf *fdf);

#endif
