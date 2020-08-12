#include "libparse.h"

/*
** 1. Skip `""`
** 2. Determine the type of light source
** 3. Clean all allocated memory and exit
*/

static void	parse_light_type(char *value, t_parse *p, t_lights *light, t_rt *rt)
{
	size_t		n;

	n = ft_strlen(value);
	value[n - 1] = '\0';
	if (ft_strcmp(value + 1, "dot") == 0)
		light->type = dot;
	else if (ft_strcmp(value + 1, "directional") == 0)
		light->type = directional;
	else if (ft_strcmp(value + 1, "ambient") == 0)
		light->type = ambient;
	else
		parse_error(p, rt, value, "nonexistent light type\n");
}

static void	parse_light_position(char *value, t_parse *p, t_lights *light,
																	t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	light->position = vec3(ft_atof_rtv(coords[0]),
							ft_atof_rtv(coords[1]),
							ft_atof_rtv(coords[2]));
	(p->fl_position)++;
	ft_free_char_arr(&coords);
}

static void	light_values(t_dict *head, char *content, char *s, t_rt *rt)
{
	t_lights	light;
	char		*value;
	t_parse		p;

	value = NULL;
	ft_clear_light(&light);
	init_parse(&p, content, head, s);
	if ((value = get_dict_value(&head, "type")) != NULL)
		parse_light_type(value, &p, &light, rt);
	if ((value = get_dict_value(&head, "position")) != NULL)
		parse_light_position(value, &p, &light, rt);
	if ((value = get_dict_value(&head, "intensity")) != NULL)
		parse_light_intensity(value, &p, &light, rt);
	push_back_light(&rt->light, new_light(light));
	required_light_fields_check(&p, &light, rt);
	ft_strdel(&p.content);
}

void		parse_lights(t_rt *rt, size_t *i, size_t j, char *s)
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
	while (s[*i] != bracket)
	{
		content = get_content(bracket, s, i, j);
		head = check_dict_values(content, rt, s);
		if (!has_duplicates(&head))
			light_values(head, content, s, rt);
		else
			parse_error_basic(content, rt, s, "duplicate keys are invalid\n");
		ft_strdel(&content);
		dict_clear(&head);
		if (s[*i] == bracket)
			break ;
		(*i)++;
	}
}
