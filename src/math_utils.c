#include "../inc/fdf.h"

double	calculate_distance(t_ivec2 point1, t_ivec2 point2)
{
	t_vec2	delta;
	double	distance;

	delta.x = abs(point2.x - point1.x);
	delta.y = abs(point2.y - point1.y);
	distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	return (distance);
}

double	calculate_edge_function(t_ivec2 vertex_a, t_ivec2 vertex_b, t_ivec2 point)
{
	return ((vertex_b.x - vertex_a.x) * (point.y - vertex_a.y) 
		- (vertex_b.y - vertex_a.y) * (point.x - vertex_a.x));
}