#include "libparse.h"

void	init_parse(t_parse *p, char *content, t_dict *head, char *s)
{
	p->content = ft_strdup(content);
	p->head = head;
	p->s = s;
	p->fl_intensity = 0;
	p->fl_position = 0;
	p->fl_look_at = 0;
	p->fl_angle = 0;
	p->fl_normal = 0;
	p->fl_radius = 0;
	p->fl_torus_radius = 0;
	p->fl_center = 0;
	p->fl_sliced_up = 0;
	p->fl_len_up = 0;
	p->fl_len_down = 0;
}

/*
** [val1, val2, val3]. Every check except opening `[` are in validation
*/

void	check_value_form(char *value, t_parse *p, t_rt *rt)
{
	if (value[0] != '[')
		parse_error(p, rt, value, "value has invalid form\n");
}

char	**parse_coords(char *value, t_rt *rt, t_parse *p)
{
	char	**coords;
	char	*tmp;
	size_t	len;

	if (!(coords = (char **)ft_memalloc(sizeof(char *) * (COORDS_LEN + 1))))
		parse_error(p, rt, value, "failed to malloc for a 2d array\n");
	coords[3] = NULL;
	tmp = NULL;
	if ((tmp = ft_strnchr(value, ',', 1)) != NULL)
		coords[0] = ft_strndup(value + 1, tmp - value - 1);
	len = ft_strlen(coords[0]) + 1;
	if ((tmp = ft_strnchr(value, ',', 2)) != NULL)
		coords[1] = ft_strndup(value + len + 1, (tmp - value) - len - 1);
	len = ft_strlen(tmp) - 1;
	coords[2] = ft_strndup(tmp + 1, len - 1);
	return (coords);
}

char	*get_content(char bracket, char *s, size_t *i, size_t j)
{
	if (bracket == ']')
		*i += 2;
	else
		(*i)++;
	if (s[*i] == '[' && s[*i + 1] == '{')
		*i += 2;
	else if (s[*i] == '{')
		(*i)++;
	j = *i;
	while (s[*i] != '}')
		(*i)++;
	return (ft_strndup(s + j, *i - j));
}
