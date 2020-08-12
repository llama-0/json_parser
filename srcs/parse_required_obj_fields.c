#include "libparse.h"
#include <stdio.h>

/*
**	A function to determine the minimum set of fields
**	required to construct a scene with provided objects, i.e.
**	- a sphere could not be displayed without knowing its radius
**	- a cone -- without angle
**	- a plane -- without normal
**		and etc.
*/

void	required_obj_fields_check(t_parse *p, t_object *object, t_rt *rt)
{
	if (object->type == plane)
	{
		if (!p->fl_center || !p->fl_normal)
			parse_error(p, rt, NULL, "not enough data to render a plane\n");
	}
	else if (object->type == sphere)
	{
		if (!p->fl_center || !p->fl_radius)
			parse_error(p, rt, NULL, "not enough data to render a sphere\n");
	}
	else if (object->type == cylinder)
	{
		if (!p->fl_center || !p->fl_normal || !p->fl_radius)
			parse_error(p, rt, NULL, "not enough data to render a cylinder\n");
	}
	else if (object->type == cone)
	{
		if (!p->fl_center || !p->fl_angle || !p->fl_normal)
			parse_error(p, rt, NULL, "not enough data to render a cone\n");
	}
	else if (object->type == torus)
	{
		if (!p->fl_center || !p->fl_radius || !p->fl_torus_radius)
			parse_error(p, rt, NULL, "not enough data to render a torus\n");
	}
}

void	parse_obj_center(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	object->center = vec3(ft_atof_rtv(coords[0]),
							ft_atof_rtv(coords[1]),
							ft_atof_rtv(coords[2]));
	p->fl_center++;
	ft_free_char_arr(&coords);
}

void	parse_obj_normal(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	object->normal = vec3(ft_atof_rtv(coords[0]),
							ft_atof_rtv(coords[1]),
							ft_atof_rtv(coords[2]));
	p->fl_normal++;
	ft_free_char_arr(&coords);
}

void	parse_obj_radius(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "radius should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "radius should be > 0\n");
	object->radius = ft_atof_rtv(value);
	if (object->radius == -1)
		parse_error(p, rt, value, "radius should be in (0, INT_MAX]\n");
	p->fl_radius++;
}

void	parse_obj_angle(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "angle should be a number\n");
	object->angle = ft_atof_rtv(value);
	if (*value == '-')
		parse_error(p, rt, value, "angle should be > 0\n");
	if (object->angle == PI_OVER_TWO)
		parse_error(p, rt, value, "angle can't be pi / 2\n");
	if (object->angle == 0.0 || object->angle >= PI)
		parse_error(p, rt, value, "angle should be in (0, 180)\n");
	object->angle = tan(object->angle * M_PI / PI);
	p->fl_angle++;
}
