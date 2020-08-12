#include "libparse.h"

void	parse_obj_sliced_up(char *value, t_parse *p,
								t_object *object, t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	object->sliced_up = vec3(ft_atof_rtv(coords[0]),
								ft_atof_rtv(coords[1]),
								ft_atof_rtv(coords[2]));
	ft_free_char_arr(&coords);
	if (v3_length(object->sliced_up) != 0.0)
	{
		object->sliced = 1;
		p->fl_sliced_up++;
	}
	else
		parse_error(p, rt, value, "sliced_up should be filled\n");
}

void	parse_obj_len_up(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "len_up should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "len_up should be in (0, 1000]\n");
	object->len_up = ft_atof_rtv(value);
	p->fl_len_up++;
}

void	parse_obj_len_down(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "len_down should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "len_down should be in [0, 1000]\n");
	object->len_down = ft_atof_rtv(value);
	p->fl_len_down++;
}
