/* ************************************************************************** */

/*                                                                            */

/*                                                        :::      ::::::::   */

/*   fdf.h                                              :+:      :+:    :+:   */

/*                                                    +:+ +:+        
	+:+      */

/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+      
	+#+        */

/*                                                +#+#+#+#+#+  
	+#+            */

/*   Created: 2024/12/13 19:42:41 by peda-cos          #+#    #+#              */

/*   Updated: 2024/12/16 23:59:59 by peda-cos         ###   ########.fr        */

/*                                                                            */

/* ************************************************************************** */



#ifndef FDF_H
# define FDF_H


# include "./lib/MLX42/include/MLX42/MLX42.h"
# include "./lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_point

{

	long x;

	long y;

	long value;

	unsigned int color;

} t_point;



typedef struct s_map

{

	int height;

	int width;

	int max;

	int min;

	long range;

	t_point **grid;

} t_map;



typedef struct s_screen

{

	int half_tile_width;

	int half_tile_height;

	int margin_x;

	int margin_y;

	int start_x;

} t_screen;



typedef struct s_mlx

{

	mlx_t *mlx;

	mlx_image_t *img;

	t_map *map;

	t_screen screen;

} t_mlx;



typedef struct s_bresenham

{

	long dx;

	long dy;

	long step_x;

	long step_y;

	long error;

	long error2;

	long total_length;

	unsigned int color;

} t_bresenham;



typedef struct s_color

{

	int r;

	int g;

	int b;

	int a;

} t_color;



typedef enum e_direction

{

	UP,

	DOWN,

	LEFT,

	RIGHT

} t_direction;

typedef struct s_rotation
{
	double	x_angle;
	double	y_angle;
	double	z_angle;
}	t_rotation;

static const int			g_resolution_x = 1200;

static const int			g_resolution_y = 800;

static const int			g_move_amount = 100;

static const unsigned int	g_red = 0xFF0000FF;

static const unsigned int	g_blue = 0x0000FFFF;

static const unsigned int	g_black = 0x000000FF;

static const unsigned int	g_bg_color = 0x000000FF;


void	rotate_map(t_mlx *mlx_instance, t_map *map, t_rotation rotation);

void	run_fdf(t_mlx *mlx_instance, t_map *map);

void	skip_lines(int fd);

int	parse_map(char *filename, t_map *map);

void	cleanup_exit(t_mlx *mlx_instance, int exit_code);

int	free_str_array(char **array);

int	allocate_map(t_map *map);

int	free_and_return(void *pointer, int return_code);

int	free_grid(t_map *map, int return_code);

unsigned int	calculate_interpolation(long start, long end, long numerator,
		long max);

int	calculate_distance(t_point point1, t_point point2);

unsigned int	calculate_gradient(t_point point1, t_point point2,
		int total_length);

void	set_point_color(t_point *point, t_map map);

void	fill_background(t_mlx *mlx_instance, unsigned int color);

void	draw_line(mlx_image_t *image, t_point point1, t_point point2);

void	handle_key_event(mlx_key_data_t key_data, void *param);

void	move_map(t_mlx *mlx_instance, t_direction direction);

void	draw_grid(t_mlx *mlx_instance, t_map *map);

void	zoom_increase(t_mlx *mlx_instance);

void	zoom_decrease(t_mlx *mlx_instance);



/* Helpers */

void	close_safe(int *fd);

int	safe_exit_on_error(void *ptr1, void *ptr2, int fd, int ret_code);



#endif
