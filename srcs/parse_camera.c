#include "libparse.h"

static void	parse_camera_position(char *value, t_parse *p,
								t_camera *camera, t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	camera->position = vec3(ft_atof_rtv(coords[0]),
							ft_atof_rtv(coords[1]),
							ft_atof_rtv(coords[2]));
	(p->fl_center)++;
	ft_free_char_arr(&coords);
}

static void	parse_camera_direction(char *value, t_parse *p,
								t_camera *camera, t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	camera->look_at = vec3(ft_atof_rtv(coords[0]),
								ft_atof_rtv(coords[1]),
								ft_atof_rtv(coords[2]));
	(p->fl_look_at)++;
	ft_free_char_arr(&coords);
}

static void	camera_values(t_dict *head, char *content, char *s, t_rt *rt)
{
	t_camera	camera;
	char		*value;
	t_parse		p;

	value = NULL;
	ft_clear_camera(&camera);
	init_parse(&p, content, head, s);
	if ((value = get_dict_value(&head, "position")) != NULL)
		parse_camera_position(value, &p, &rt->camera, rt);
	if ((value = get_dict_value(&head, "look_at")) != NULL)
		parse_camera_direction(value, &p, &rt->camera, rt);
	if (!p.fl_look_at || !p.fl_center)
	{
		parse_error(&p, rt, content,
						"camera key(s) are invalid OR missing second key\n");
	}
	ft_strdel(&p.content);
}

static void	del_local(char *content, t_dict *head)
{
	ft_strdel(&content);
	dict_clear(&head);
}

void		parse_camera(t_rt *rt, size_t *i, size_t j, char *s)
{
	t_dict	*head;
	char	*content;
	char	bracket;

	bracket = '0';
	if (ft_key_list_size(rt->key) > 1)
		*i += 4;
	if (s[*i] == '[')
		bracket = ']';
	else if (s[*i] == '{')
		bracket = '}';
	if (s[*i] == '{' || s[*i] == '[')
	{
		content = get_content(bracket, s, i, j);
		head = check_dict_values(content, rt, s);
		if (!has_duplicates(&head))
			camera_values(head, content, s, rt);
		else
			parse_error_basic(content, rt, s, "duplicate keys are invalid\n");
		if (s[*i] == '}' && s[*i + 1] == ',' && s[*i + 2] == '{')
			parse_error_basic(content, rt, s, "too many cameras :)\n");
		if (bracket == ']')
			(*i)++;
		del_local(content, head);
	}
}
