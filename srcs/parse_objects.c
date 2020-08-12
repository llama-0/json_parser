#include "libparse.h"

void	parse_obj_type(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	size_t	n;

	n = ft_strlen(value);
	value[n - 1] = '\0';
	if (ft_strcmp(value + 1, "plane") == 0)
		object->type = plane;
	else if (ft_strcmp(value + 1, "sphere") == 0)
		object->type = sphere;
	else if (ft_strcmp(value + 1, "cylinder") == 0)
		object->type = cylinder;
	else if (ft_strcmp(value + 1, "cone") == 0)
		object->type = cone;
	else if (ft_strcmp(value + 1, "torus") == 0)
		object->type = torus;
	else
		parse_error(p, rt, value, "nonexistent object type\n");
}

void	object_values(t_dict *head, char *content, char *s, t_rt *rt)
{
	t_object	object;
	char		*value;
	t_parse		p;

	value = NULL;
	ft_clear_object(&object);
	init_parse(&p, content, head, s);
	if ((value = get_dict_value(&head, "type")) != NULL)
		parse_obj_type(value, &p, &object, rt);
	else
		parse_error(&p, rt, value,
					"object type not present in a source file\n");
	object_values_required(value, &p, &object, rt);
	other_object_values(value, &p, &object, rt);
	advanced_object_values(value, &p, &object, rt);
	sliced_object_values(value, &p, &object, rt);
	push_back_obj(&rt->object, new_obj(object));
	required_obj_fields_check(&p, &object, rt);
	ft_strdel(&p.content);
}

void	parse_objects(t_rt *rt, size_t *i, size_t j, char *s)
{
	t_dict		*head;
	char		*content;
	char		bracket;

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
			object_values(head, content, s, rt);
		else
			parse_error_basic(content, rt, s, "duplicate keys are invalid\n");
		ft_strdel(&content);
		dict_clear(&head);
		if (bracket == '}')
			break ;
		(*i)++;
	}
}
