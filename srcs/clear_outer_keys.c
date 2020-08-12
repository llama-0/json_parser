#include "libparse.h"

void	ft_clear_light(t_lights *light)
{
	light->id = 0;
	light->type = nonexistent;
	light->position = vec3(0, 0, 0);
	light->intensity = 0.0;
}

void	ft_clear_camera(t_camera *camera)
{
	camera->look_at = vec3(0, 0, 0);
	camera->position = vec3(0, 0, 0);
}

void	ft_clear_object(t_object *object)
{
	object->id = 0;
	object->type = none;
	object->center = vec3(0, 0, 0);
	object->normal = vec3(0, 0, 0);
	object->radius = 0.0;
	object->torus_radius = 0.0;
	object->angle = 0.0;
	object->color = 0;
	object->specular = 0;
	object->translation = vec3(0, 0, 0);
	object->rotation = vec3(0, 0, 0);
	object->reflective = 0.0;
	object->transparancy = 0.0;
	object->transparancy_percent = 0.0;
	object->sliced = 0;
	object->sliced_up = vec3(0, 0, 0);
	object->len_up = 0.0;
	object->len_down = 0.0;
	object->negative = 0;
}
