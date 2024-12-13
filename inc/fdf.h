/* ************************************************************************** */
/*																		    */
/*												        :::      ::::::::   */
/*   fdf.h									          :+:      :+:    :+:   */
/*												    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*												+#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:42:41 by peda-cos          #+#    #+#			 */
/*   Updated: 2024/12/13 19:42:41 by peda-cos         ###   ########.fr       */
/*																		    */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

typedef struct s_point
{
	long			x;
	long			y;
	long			value;
	unsigned int	c;
}					t_point;

typedef struct s_map
{
	int				h;
	int				w;
	int				max;
	int				min;
	long			range;
	t_point         **grid;
}				      t_map;

typedef struct s_screen
{
	int				half_tiles;
	int				half_tile_w;
	int				half_tile_h;
	int				mar_x;
	int				mar_y;
	int				start_x;
}					t_screen;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img1;
	t_map			*map;
	t_screen		s;
}					t_mlx;

typedef struct s_br
{
	long			dx;
	long			ddx;
	long			dy;
	long			ddy;
	long			sx;
	long			sy;
	long			err;
	long			e2;
	long			t_l;
	unsigned int	color;
}					t_br;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_color;

typedef enum e_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_dir;

const static int          g_res_x = 1200;
const static int          g_res_y = 800;
const static int          g_mv_amt = 100;
const static unsigned int g_red = 0xFF0000FF;
const static unsigned int g_blue = 0x0000FFFF;
const static unsigned int g_black = 0x000000FF;
const static unsigned int g_c1 = 0x0000FFFF;
const static unsigned int g_c2 = 0xFF0000FF;
const static unsigned int g_bg_c = 0x000000FF;

void    run_fdf(t_mlx *m, t_map *mp);
void    skip_line(int fd);
int     parse_map(char *file, t_map *mp);
void    cleanup_exit(t_mlx *m, int r);
int     free_strarr(char **arr);
int     alloc_map(t_map *mp);
int     free_ret(void *p, int r);
int     free_grid(t_map *mp, int r);
unsigned int calc_ip(long s, long e, long n, long mx);
int     calc_dist(t_point p1, t_point p2);
unsigned int calc_grad(t_point p1, t_point p2, int tl);
void    set_pt_clr(t_point *p, t_map mp);
void    fill_bg(t_mlx *m, unsigned int clr);
void    draw_ln(mlx_image_t *img, t_point p1, t_point p2);
void    handle_key(mlx_key_data_t kd, void *prm);
void    shift_map(t_mlx *m, t_dir d);
void    draw_grid(t_mlx *m, t_map *mp);
void    zoom_inc(t_mlx *m);
void    zoom_dec(t_mlx *m);

#endif
