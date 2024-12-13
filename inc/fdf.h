/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/13 13:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

typedef struct s_point
{
	long            x;
	long            y;
	long            value;
	unsigned int    c;
}                   t_point;

typedef struct s_map
{
	int             h;
	int             w;
	int             max;
	int             min;
	long            range;
	t_point         **grid;
}                   t_map;

typedef struct s_screen
{
	int             half_tiles;
	int             half_tile_w;
	int             half_tile_h;
	int             mar_x;
	int             mar_y;
	int             start_x;
}                   t_screen;

typedef enum e_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}                   t_dir;

typedef enum e_auto
{
	AUTO_STOP = 0,
	AUTO_CW,
	AUTO_CCW
}                   t_auto;

typedef enum e_proj
{
	PROJ_ISO = 0,
	PROJ_TOP
}                   t_proj;

typedef struct s_cam
{
	double          x_off;
	double          y_off;
	double          x_ang;
	double          y_ang;
	double          z_ang;
	double          z_fac;
	double          scl;
	double          scl_w;
	double          scl_h;
	int             line_type;  
	t_proj          proj;
	t_auto          arot_x;
	t_auto          arot_y;
	t_auto          arot_z;
}                   t_cam;

typedef struct s_mlx
{
	mlx_t           *mlx;
	mlx_image_t     *img1;
	t_map           *map;
	t_screen        s;
	t_cam           cam;
}                   t_mlx;

const static int          g_res_x = 1200;
const static int          g_res_y = 800;
const static int          g_mv_amt = 20;
const static double       g_pi = 3.14159265359;

const static unsigned int g_blue = 0x0000FFFF;
const static unsigned int g_red = 0xFF0000FF;
const static unsigned int g_black = 0x000000FF;
const static unsigned int g_c1 = 0x0000FFFF;
const static unsigned int g_c2 = 0xFF0000FF;
const static unsigned int g_bg_c = 0x000000FF;

void            run_fdf(t_mlx *m, t_map *mp);
void            skip_line(int fd);
int             parse_map(char *file, t_map *mp);
void            cleanup_exit(t_mlx *m, int r);
int             free_strarr(char **arr);
int             alloc_map(t_map *mp);
int             free_ret(void *p, int r);
int             free_grid(t_map *mp, int r);

unsigned int    calc_ip(long s, long e, long n, long mx);
int             calc_dist(t_point p1, t_point p2);

unsigned int    calc_grad(t_point p1, t_point p2, int tl);
void            set_pt_clr(t_point *p, t_map mp);
void            fill_bg(t_mlx *m, unsigned int clr);

void            draw_line(mlx_image_t *img, t_point p1, t_point p2);
void            bresenham_algorithm(mlx_image_t *img, t_point p1, t_point p2);

void            handle_key(mlx_key_data_t kd, void *prm);
void            manage_keys(t_mlx *m);

void            init_cam(t_mlx *m);
void            apply_transformations(t_mlx *m);

void            frame_hook(void *param);
void            draw_grid(t_mlx *m, t_map *map);

void            show_menu(t_mlx *m);
void            move(t_mlx *mlx, t_dir dir);

#endif
