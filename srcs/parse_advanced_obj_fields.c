#include "libparse.h"

/*
** torus (tube) radius considered to be advanced,
** but it's also a required obj field.
**
** Future improvements:
** R > r: ring torus or anchor ring (implemented)
** R=r: horn torus (not implemented)
** R < r: self-intersecting spindle torus (not implemented)
*/

void	parse_obj_torus_radius(char *value, t_parse *p, t_object *object,
																	t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "radius should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "radius should be > 0\n");
	object->torus_radius = ft_atof_rtv(value);
	if (object->torus_radius == -1)
		parse_error(p, rt, value, "radius should be in (0, INT_MAX]\n");
	p->fl_torus_radius++;
}

void	parse_obj_reflective(char *value, t_parse *p, t_object *object,
																t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "reflective should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "reflective should be >= 0\n");
	object->reflective = ft_atof_rtv(value);
	if (!(ft_check_range(object->reflective, 1)))
		parse_error(p, rt, value, "reflective should be in [0, 1]\n");
}

void	parse_obj_transparency(char *value, t_parse *p, t_object *object,
																t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "transparancy should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "transparancy should be posotive\n");
	object->transparancy = ft_atof_rtv(value);
	if (!(ft_check_range(object->transparancy, 0)))
		parse_error(p, rt, value, "transparancy should be in (1, 2)\n");
}

void	parse_obj_transparency_percent(char *value, t_parse *p,
										t_object *object, t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "transparancy_percent should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "transparancy_percent should be > 0\n");
	object->transparancy_percent = ft_atof_rtv(value);
	if (!(ft_check_range(object->transparancy_percent, 1))
		|| object->transparancy_percent == 0.0)
		parse_error(p, rt, value, "transparancy_percent should be in (0, 1]\n");
}

void	parse_obj_negative(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	int	neg;

	if (*value == '"')
		parse_error(p, rt, value, "negative should be a number\n");
	neg = ft_atoi_rtv(value);
	if (neg == 0 || neg == 1)
		object->negative = neg;
	else
		parse_error(p, rt, value, "negative should be 1 or 0\n");
}
