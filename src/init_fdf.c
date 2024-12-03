#include "../inc/fdf.h"

static void	calculate_mesh(char *file_path, t_FdF *fdf_data)
{
	int16_t		file_descriptor;
	char		current_char;
	char		previous_char;

	file_descriptor = open(file_path, O_RDONLY);
	if (file_descriptor == -1)
		clean_exit(file_path, fdf_data);
	previous_char = ' ';
	while (read(file_descriptor, &current_char, 1))
	{
		if (!ft_isspace(current_char) && ft_isspace(previous_char))
			fdf_data->vertex_count++;
		if (current_char == '\n')
			fdf_data->mesh_height++;
		if (current_char == '\n' && !fdf_data->mesh_width)
			fdf_data->mesh_width = fdf_data->vertex_count;
		previous_char = current_char;
	}
	if (current_char != '\n')
		fdf_data->mesh_height++;
	if (!fdf_data->mesh_width)
		fdf_data->mesh_width = fdf_data->vertex_count;
	close(file_descriptor);
	if (!fdf_data->vertex_count || 
	    fdf_data->mesh_width * fdf_data->mesh_height != fdf_data->vertex_count)
		clean_exit("Map error", fdf_data);
}

static int32_t	parse_next_value(int file_descriptor, t_FdF *fdf_data)
{
	int		bytes_read;
	int		buffer_index;
	char	value_buffer[64];

	bytes_read = 1;
	buffer_index = 0;
	while (bytes_read && buffer_index < 63)
	{
		bytes_read = read(file_descriptor, &value_buffer[buffer_index], 1);
		if (bytes_read == -1)
		{
			close(file_descriptor);
			clean_exit("Read failed", fdf_data);
		}
		if (buffer_index && ft_isspace(value_buffer[buffer_index]))
			break ;
		if (!ft_isspace(value_buffer[buffer_index]) && bytes_read)
			buffer_index++;
	}
	value_buffer[buffer_index] = '\0';
	validate_value(value_buffer, fdf_data);
	return (ft_atoi(value_buffer));
}

static void	populate_mesh(char *file_path, t_FdF *fdf_data)
{
	int		file_descriptor;
	size_t	vertex_index;
	size_t	current_x;
	size_t	current_y;

	file_descriptor = open(file_path, O_RDONLY);
	if (file_descriptor == -1)
		clean_exit(file_path, fdf_data);
	vertex_index = 0;
	current_x = 0;
	current_y = 0;
	while (vertex_index < fdf_data->vertex_count)
	{
		fdf_data->mesh[vertex_index].x = current_x;
		fdf_data->mesh[vertex_index].y = current_y;
		fdf_data->mesh[vertex_index].z = parse_next_value(file_descriptor, fdf_data);
		vertex_index++;
		current_x++;
		if (current_x == fdf_data->mesh_width)
		{
			current_y++;
			current_x = 0;
		}
	}
	close(file_descriptor);
}

void	init_fdf(char *file_path, t_FdF *fdf_data)
{
	calculate_mesh(file_path, fdf_data);
	fdf_data->mesh = (t_vert *)malloc(fdf_data->vertex_count * sizeof(t_vert));
	if (!fdf_data->mesh)
		clean_exit("Memory allocation failed", fdf_data);
	populate_mesh(file_path, fdf_data);
	set_vert_colors(fdf_data);
	fdf_data->height_scale = 1;
}