#include "libparse.h"
#include <stdio.h>

void	v3_print(t_vec3 v)
{
	printf("(%lf, %lf, %lf)\n", v.x, v.y, v.z);
}

void	print_key_list(t_key **head)
{
	t_key	*key;

	key = *head;
	printf("\tkeys:\n");
	while (key)
	{
		printf("%s\n", key->content);
		key = key->next;
	}
	printf("\tend of keys\n");
}

void	print_light_list(t_lights **head)
{
	t_lights *light;

	light = *head;
	printf("\x1B[33m\tlights: \n\x1B[0m");
	while (light)
	{
		printf("type: %u\n", light->type);
		printf("direction: ");
		v3_print(light->position);
		printf("intensity: %f\n", light->intensity);
		light = light->next;
	}
	printf("\x1B[33m\tend of lights\n\x1B[0m");
}

void		print_object_list(t_object **head)
{
	t_object	*object;

	object = *head;
	printf("\x1B[32m\tobjects: \n\x1B[0m");
	while (object)
	{
		printf("type: %u\n", object->type);
		printf("center: ");
		v3_print(object->center);
		printf("normal: ");
		v3_print(object->normal);
		printf("radius: %f\n", object->radius);
		printf("torus radius: %f\n", object->torus_radius);
		printf("angle: %f\n", object->angle);
		printf("color: %d\n", object->color);
		printf("specular: %d\n", object->specular);
		printf("translation: ");
		v3_print(object->translation);
		printf("rotation: ");
		v3_print(object->rotation);
		printf("reflective: %f\n", object->reflective);
		printf("transparancy: %f\n", object->transparancy);
		printf("transparancy_percent: %f\n", object->transparancy_percent);
		printf("sliced: %u\n", object->sliced);
		printf("slised_up: ");
		v3_print(object->sliced_up);
		printf("len_up: %f\n", object->len_up);
		printf("len_down: %f\n", object->len_down);
		printf("negative: %u\n\n", object->negative);
		object = object->next;
	}
	printf("\x1B[32m\tend of objects\n\x1B[0m");
}