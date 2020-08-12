#include "libparse.h"

void	object_values_required(char *value, t_parse *p,
								t_object *object, t_rt *rt)
{
	if ((value = get_dict_value(&p->head, "center")) != NULL)
		parse_obj_center(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "radius")) != NULL)
		parse_obj_radius(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "tube_radius")) != NULL)
		parse_obj_torus_radius(value, p, object, rt);
	if (object->type == torus && object->radius <= object->torus_radius)
		parse_error(p, rt, NULL, "we render only doughnuts, R > r\n");
	if ((value = get_dict_value(&p->head, "normal")) != NULL)
		parse_obj_normal(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "angle")) != NULL)
		parse_obj_angle(value, p, object, rt);
}

void	other_object_values(char *value, t_parse *p,
								t_object *object, t_rt *rt)
{
	if ((value = get_dict_value(&p->head, "color")) != NULL)
		parse_obj_color(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "specular")) != NULL)
		parse_obj_specular(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "translation")) != NULL)
		parse_obj_translation(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "rotation")) != NULL)
		parse_obj_rotation(value, p, object, rt);
}

void	advanced_object_values(char *value, t_parse *p,
								t_object *object, t_rt *rt)
{
	if ((value = get_dict_value(&p->head, "reflective")) != NULL)
		parse_obj_reflective(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "transparency")) != NULL)
		parse_obj_transparency(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "transparency_percent")) != NULL)
		parse_obj_transparency_percent(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "negative")) != NULL)
		parse_obj_negative(value, p, object, rt);
}

void	sliced_object_values(char *value, t_parse *p,
								t_object *object, t_rt *rt)
{
	if ((value = get_dict_value(&p->head, "sliced_up")) != NULL)
		parse_obj_sliced_up(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "len_up")) != NULL)
		parse_obj_len_up(value, p, object, rt);
	if ((value = get_dict_value(&p->head, "len_down")) != NULL)
		parse_obj_len_down(value, p, object, rt);
	if (p->fl_sliced_up && (!p->fl_len_up || !p->fl_len_down))
		parse_error(p, rt, NULL,
			"also need len_up & len_down to render a sliced object\n");
	else if (p->fl_len_up && (!p->fl_sliced_up || !p->fl_len_down))
		parse_error(p, rt, NULL,
			"also need sliced_up & len_down to render a sliced object\n");
	else if (p->fl_len_down && (!p->fl_sliced_up || !p->fl_len_up))
		parse_error(p, rt, NULL,
			"also need sliced_up & len_up to render a sliced object\n");
}
