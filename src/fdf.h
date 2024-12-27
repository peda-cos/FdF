/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:32:22 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:33:30 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define PI 3.14159265359
# define WIDTH 1280
# define HEIGHT 720

typedef struct s_map
{
	float	x;
	float	y;
	int		z;
	int		color;
}	t_map;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_draw_parameters
{
	int		delta_x;
	int		delta_y;
	int		step_x;
	int		step_y;
	int		decision;
	float	current_x;
	float	current_y;
}	t_draw_parameters;

typedef struct s_map_dimensions
{
	size_t	width;
	size_t	height;
}	t_map_dimensions;

typedef struct s_map_offset
{
	int	start_x;
	int	start_y;
	int	scaling_interval;
}	t_map_offset;

typedef struct s_position
{
	unsigned int	x;
	unsigned int	y;
}	t_position;

typedef struct s_line_coordinates
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
}	t_line_coordinates;

/*
**  Prototipagem das funções.
*/

/* main.c */
int			main(int argc, char *argv[]);
void		handle_mlx_events(void *param);
void		print_error_and_exit(void);

/* map_manager.c */
int			read_and_draw_map(mlx_image_t *image, char *file_path);
int			handle_map(mlx_t *mlx_ptr, mlx_image_t *image, char *file_path);

/* parse_map.c */
size_t		get_file_line_count(char *file_path);
char		**read_file_lines(char *file_path, size_t line_count);
t_map		**parse_map_data(char **map_lines, size_t height,
				t_map_dimensions *map_dims);
void		free_string_array(char **ptr, size_t size);
void		free_map_data(t_map **map_data, size_t height);

/* parse_map_utils.c */
void		fill_map_element(t_map *map_element, char *value,
				unsigned int x_idx, unsigned int y_idx);
bool		check_map_columns(char **values, t_map_dimensions *map_dims,
				unsigned int current_row);
bool		allocate_and_fill_map_row(char **values, t_map **map_data,
				unsigned int current_row, t_map_dimensions *map_dims);
bool		process_map_row(t_map **map_data, t_map_dimensions *map_dims,
				char **map_lines, unsigned int current_row);
size_t		get_string_array_width(char **values);

/* line_drawing.c */
void		draw_shallow_line(t_draw_parameters *draw_params,
				mlx_image_t *image, int start_color, int end_color);
void		draw_steep_line(t_draw_parameters *draw_params,
				mlx_image_t *image, int start_color, int end_color);
void		draw_map(mlx_image_t *image, t_map **map_data,
				t_map_dimensions *map_dims);

/* line_drawing_utils.c */
void		draw_diagonal_line(mlx_image_t *image,
				t_draw_parameters *draw_params, int start_color,
				int end_color);
void		draw_horizontal_line(mlx_image_t *image, t_map **map_data,
				t_draw_parameters *draw_params, t_position *pos);
void		draw_vertical_line(mlx_image_t *image, t_map **map_data,
				t_draw_parameters *draw_params, t_position *pos);

/* line_parameters.c */
void		set_line_parameters(t_draw_parameters *draw_params,
				t_line_coordinates *coords);
void		set_map_offset(t_map_offset *offset, t_map_dimensions *map_dims);
int			get_step_direction(float start_point, float end_point);
int			get_axis_difference(float start_point, float end_point);

/* transformations.c */
void		rescale_map(t_map **map_data, t_map_dimensions *map_dims);
void		zoom_map(t_map **map_data, t_map_offset *offset,
				unsigned int x_idx, unsigned int y_idx);
float		get_x_derivative(float x_val, float y_val, int z_val);
float		get_y_derivative(float x_val, float y_val, int z_val);

/* color_utils.c */
int			get_color_gradient(int start_color, int end_color,
				int position, int length);
void		set_default_color(int *color_ref, int z_val);
int			parse_hex_string(const char *hex_str);

#endif
