/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:58:43 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:53:23 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <fcntl.h>
# include <math.h>
# include <sys/errno.h>

# ifndef CURSOR_SETTABLE
#  define CURSOR_SETTABLE 1
# endif

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720

# define R 3
# define G 2
# define B 1
# define A 0

typedef union u_color
{
	uint32_t	color;
	uint8_t		channel[4];
}				t_color;

typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct s_ivec2
{
	int32_t		x;
	int32_t		y;
}				t_ivec2;

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_pixel
{
	union
	{
		t_ivec2		pos;
		struct
		{
			int32_t	x;
			int32_t	y;
		};
	};
	double			depth;
	union
	{
		uint32_t	color;
		uint8_t		channel[4];
	};
	int8_t			vis;
	double			u;
	double			v;
}					t_pixel;

typedef struct s_vert
{
	union
	{
		t_vec3		pos;
		struct
		{
			double	x;
			double	y;
			double	z;
		};
	};
	t_pixel			pixel;
	t_vec3			world;
}					t_vert;

typedef struct s_tri
{
	t_pixel			a;
	t_pixel			b;
	t_pixel			c;
	t_ivec2			bbox[2];
	double			weight_a;
	double			weight_b;
	double			weight_c;
	double			area;
}					t_tri;

typedef struct s_face
{
	t_vert			a;
	t_vert			b;
	t_vert			c;
	t_vert			d;
}					t_face;

typedef struct s_skybox
{
	mlx_texture_t	*ft_tex;
	mlx_texture_t	*rt_tex;
	mlx_texture_t	*bk_tex;
	mlx_texture_t	*lf_tex;
	mlx_texture_t	*up_tex;
	mlx_texture_t	*dn_tex;
	t_vert			ft[121];
	t_vert			rt[121];
	t_vert			bk[121];
	t_vert			lf[121];
	t_vert			up[121];
	t_vert			dn[121];
}					t_skybox;

typedef struct s_FdF
{
	t_vert		*mesh;
	t_vec3		x_dir;
	t_vec3		y_dir;
	t_vec3		z_dir;
	t_skybox	skybox;
	size_t		mesh_height;
	size_t		mesh_width;
	t_vec2		mesh_pos;
	size_t		vert_count;
	int32_t		max_height;
	int32_t		min_height;
	mlx_image_t	*depth_map;
	mlx_image_t	*background;
	mlx_image_t	*canvas;
	mlx_image_t	*fps_image;
	mlx_t		*mlx;
	int8_t		anti_aliasing;
	int8_t		draw_fps;
	int8_t		draw_verts;
	int8_t		draw_edges;
	int8_t		draw_dotted_edges;
	int8_t		draw_faces;
	int8_t		draw_faces_edges;
	int8_t		draw_skybox;
	t_ivec2		initial_cursor_pos;
	double		height_scale;
	double		mesh_scale;
	double		initial_mesh_scale;
	double		pitch;
	double		yaw;
	double		vert_size;
	double		dot_size;
	int16_t		dot_density;
	uint8_t		line_thickness;
	int8_t		orthographic;
	int8_t		skybox_number;
	double		clicked;
	int8_t		mouse_buttons_pressed;
	double		foc;
	double		camera_height;
}				t_fdf;

//initializer
void		initialize_fdf(char *file_path, t_fdf *fdf);
void		initialize_settings(t_fdf *fdf);
void		initialize_mlx(t_fdf *fdf);

//reader
void	reset_depth_map(t_fdf *fdf);
void	adjust_canvas_brightness(double factor, t_fdf *fdf);
void	render_background(t_fdf *fdf);
void	display_fps(t_fdf *fdf);
void	main_render_loop(void *param);

//colors
int32_t		calculate_height_color(int32_t height, t_fdf *fdf);
void		determine_min_max_height(t_fdf *fdf);
void		apply_vertex_colors(t_fdf *fdf);
uint32_t	get_texture_color(mlx_texture_t *texture, int32_t x, int32_t y);
uint32_t	get_image_color(mlx_image_t *image, int32_t x, int32_t y);
uint32_t	calculate_fade_color(uint32_t color_start, uint32_t color_end, int32_t steps, int step);
uint8_t		interpolate_color_channel(uint8_t start, uint8_t end, double factor);
uint32_t	interpolate_color(uint32_t color_start, uint32_t color_end, double factor);

//validation
uint8_t		check_range(char *number, char *min, char *max);
uint8_t		is_numeric_string(char *string);
void		validate_map_value(char *value, t_fdf *fdf);

//error handling
void	free_skybox_textures(t_fdf *fdf);
void	exit_program(char *error_message, t_fdf *fdf);

//controls
void	update_draw_mode(mlx_key_data_t key_data, t_fdf *fdf);
void	update_projection(mlx_key_data_t key_data, t_fdf *fdf);
void	adjust_line_and_dot_size(mlx_key_data_t key_data, t_fdf *fdf);
void	update_skybox(mlx_key_data_t key_data, t_fdf *fdf);
void	handle_key_event(mlx_key_data_t key_data, void *param);
void	adjust_rotation(t_vec2 movement, t_fdf *fdf);
void	handle_cursor_event(double cursor_x, double cursor_y, void *param);

//line
t_ivec2	interpolate_position(t_ivec2 start, t_ivec2 end, double factor);
void	draw_dotted_line(t_vertex vertex_a, t_vertex vertex_b, uint16_t dot_size, t_fdf *fdf);
void	update_pixel_position(t_ivec2 *position, t_ivec2 *index, uint16_t size);
void	put_dot(mlx_image_t *image, t_pixel pixel, uint16_t dot_size, t_fdf *fdf);
uint8_t	is_line_visible(t_pixel start, t_pixel end, t_fdf *fdf);
void	draw_anti_aliased_line_segment(t_vec2 position, t_pixel pixel, t_fdf *fdf);
void	draw_anti_aliased_line(t_pixel start, t_pixel end, t_fdf *fdf);
void	draw_pixel_line(t_pixel start, t_pixel end, uint8_t thickness, t_fdf *fdf);
void	draw_line(t_pixel start, t_pixel end, uint8_t thickness, t_fdf *fdf);

//mesh
void	adjust_mesh_to_center(t_fdf *fdf);
int8_t	is_fdf_file(char *file_path);
int8_t	is_png_file(char *file_path);
void	initialize_mesh(int argc, char **argv, t_fdf *fdf);
void	calculate_directions(t_fdf *fdf);
t_vec3	transform_object_to_world(t_vec3 object, t_fdf *fdf);
void	project_vertices_to_canvas(t_fdf *fdf);
void	render_mesh_dotted_edges(t_fdf *fdf);
void	render_mesh_faces(t_fdf *fdf);
void	render_mesh_edges(t_fdf *fdf);
void	render_mesh_vertices(t_fdf *fdf);
void	render_mesh(t_fdf *fdf);

//pixel
void	draw_large_pixel(mlx_image_t *image, t_pixel pixel, uint8_t size, t_fdf *fdf);
void	store_depth(t_pixel pixel, t_fdf *fdf);
float	get_depth(t_pixel pixel, t_fdf *fdf);
void	draw_anti_aliased_pixel(mlx_image_t *image, t_pixel pixel, t_fdf *fdf);
void	draw_pixel(mlx_image_t *image, t_pixel pixel, uint8_t size, t_fdf *fdf);

//skybox
void	project_skybox_vertices(t_vertex *vertices, t_fdf *fdf);
void	subdivide_skybox_face(mlx_texture_t *texture, t_vertex *vertices, t_fdf *fdf);
void	render_skybox(t_fdf *fdf);
void	render_sky_pixel(mlx_texture_t *texture, t_pixel pixel, t_triangle triangle, t_fdf *fdf);
void	render_sky_triangle(mlx_texture_t *texture, t_triangle triangle, t_fdf *fdf);

//triangle
void	draw_triangle_outlines(t_triangle triangle, t_fdf *fdf);
void	calculate_bounding_box(t_triangle *triangle, t_fdf *fdf);
void	render_triangle_pixel(t_pixel pixel, t_triangle triangle, t_fdf *fdf);
void	render_triangle(t_triangle triangle, t_fdf *fdf);
void	render_face(t_face face, t_fdf *fdf);

//vectors
t_vec3	add_vectors(t_vec3 vector_a, t_vec3 vector_b);
void	initialize_skybox_vertices(t_vertex *vertices, t_vec3 start_pos, 
	t_vec3 step1, t_vec3 step2);
void	verify_texture_allocation(mlx_texture_t *texture, char *path, t_fdf *fdf);
void	load_skybox_textures(uint8_t skybox_id, t_fdf *fdf);
void	initialize_skybox(t_fdf *fdf);

//math
double	calculate_distance(t_ivec2 point1, t_ivec2 point2);
double	calculate_edge_function(t_ivec2 vertex_a, t_ivec2 vertex_b, t_ivec2 point);

//png
void	center_mesh_height(t_fdf *fdf);
void	parse_png_to_mesh(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_fdf *fdf);
void	validate_image_dimensions(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_fdf *fdf);
void	allocate_mesh_memory(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_fdf *fdf);
void	initialize_from_png(char *heightmap_file, char *colormap_file, t_fdf *fdf);

#endif