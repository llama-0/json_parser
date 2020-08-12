#include "libparse.h"

void	parse_light_intensity(char *value, t_parse *p, t_lights *light,
																	t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "light intensity should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "intensity should be >= 0\n");
	light->intensity = ft_atof_rtv(value);
	if (!(ft_check_range(light->intensity, 1)))
		parse_error(p, rt, value, "intensity should be in [0, 1]\n");
	(p->fl_intensity)++;
}

void	required_light_fields_check(t_parse *p, t_lights *light, t_rt *rt)
{
	if (light->type == dot || light->type == directional)
	{
		if (!p->fl_position || !p->fl_intensity)
			parse_error(p, rt, NULL, "not enough data about a light source\n");
	}
	else if (light->type == ambient)
	{
		if (!p->fl_intensity)
			parse_error(p, rt, NULL, "not enough data to light a scene\n");
	}
}
