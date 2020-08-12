#include "libparse.h"

static int	is_parent_key_duplicate(char *tmp, size_t j, t_key **head)
{
	t_key	*lst;
	char	*parent_key;

	parent_key = ft_strndup(tmp + 1, j - 1);
	lst = *head;
	while (lst != NULL)
	{
		if (ft_key_find(head, parent_key) != NULL)
		{
			ft_strdel(&parent_key);
			return (1);
		}
		lst = lst->next;
	}
	add_key(head, new_key(parent_key));
	ft_strdel(&parent_key);
	return (0);
}

static void	process_json_content(t_rt *rt, size_t *i, size_t j, char *s)
{
	if (ft_strequ(rt->key->content, JSON_CAMERA))
		parse_camera(rt, i, j, s);
	else if (ft_strequ(rt->key->content, JSON_OBJECTS))
		parse_objects(rt, i, j, s);
	else if (ft_strequ(rt->key->content, JSON_LIGHTS))
		parse_lights(rt, i, j, s);
	else
		parse_error_basic(NULL, rt, s, "outer key is not recognized\n");
}

/*
** check for required scene set
** (camera and lights to display at least a background)
*/

static void	json_last_check(t_rt *rt, char *s)
{
	if (ft_key_find(&rt->key, JSON_LIGHTS) == NULL
			|| ft_key_find(&rt->key, JSON_CAMERA) == NULL)
		parse_error_basic(NULL, rt, s, "not enough data to render a scene\n");
	if (ft_key_find(&rt->key, JSON_OBJECTS) == NULL)
		ft_clear_object(rt->object);
	ft_putstr_fd("\033[0;32m", 1);
	ft_putstr_fd("DONE PARSING", 1);
	ft_putendl_fd("\033[0m", 1);
	// ft_free_key_list(&rt->key);
}

void		parse_json(char *s, t_rt *rt)
{
	char	*tmp;
	char	*tmp_old;
	size_t	i;
	size_t	j;

	tmp = s;
	i = 0;
	while (s[i] != '\0')
	{
		tmp_old = tmp;
		tmp = ft_strchr(tmp_old, '"');
		j = tmp - tmp_old;
		if (i == 0)
			i += 3;
		i += j;
		while (tmp[j] != '"' && i++)
			j++;
		if (is_parent_key_duplicate(tmp, j, &rt->key) == 1)
			parse_error_basic(NULL, rt, s, KEY_DUPLICATES);
		process_json_content(rt, &i, j, s);
		if (s[i] == 0 || s[i + 1] == 0 || s[i + 2] == 0 || s[i + 3] == 0)
			break ;
		tmp = s + i;
	}
	json_last_check(rt, s);
}
