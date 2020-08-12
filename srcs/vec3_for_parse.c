#include "libparse.h"

t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

double	v3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
