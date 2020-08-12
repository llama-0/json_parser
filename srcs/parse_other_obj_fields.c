#include "libparse.h"

void		parse_obj_translation(char *value, t_parse *p,
								t_object *object, t_rt *rt)
{
	char	**coords;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	object->translation = vec3(ft_atof_rtv(coords[0]),
								ft_atof_rtv(coords[1]),
								ft_atof_rtv(coords[2]));
	ft_free_char_arr(&coords);
}

void		parse_obj_rotation(char *value, t_parse *p, t_object *object,
																	t_rt *rt)
{
	char	**coords;
	double	x;
	double	y;
	double	z;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	if (*coords[0] == '-' || *coords[1] == '-' || *coords[2] == '-')
	{
		ft_free_char_arr(&coords);
		parse_error(p, rt, value,
			"coordinates for rotation should be non-negative\n");
	}
	x = ft_atof_rtv(coords[0]);
	y = ft_atof_rtv(coords[1]);
	z = ft_atof_rtv(coords[2]);
	if (x > PI || y > PI || z > PI)
	{
		ft_free_char_arr(&coords);
		parse_error(p, rt, value,
			"coordinates for rotation should be in [0; 180]\n");
	}
	object->rotation = vec3(x, y, z);
	ft_free_char_arr(&coords);
}

void		parse_obj_specular(char *value, t_parse *p, t_object *object,
																	t_rt *rt)
{
	if (*value == '"')
		parse_error(p, rt, value, "specular should be a number\n");
	if (*value == '-')
		parse_error(p, rt, value, "specular should be non-negative\n");
	if ((object->specular = ft_atoi_rtv(value)) < 0)
		parse_error(p, rt, value, "specular should be in [0; INT_MAX]\n");
}

static void	parse_obj_color_rgb(char *value, t_parse *p, t_object *object,
																	t_rt *rt)
{
	char	**coords;
	int		r;
	int		g;
	int		b;

	check_value_form(value, p, rt);
	coords = parse_coords(value, rt, p);
	if (*coords[0] == '-' || *coords[1] == '-' || *coords[2] == '-')
	{
		ft_free_char_arr(&coords);
		parse_error(p, rt, value,
			"color in rgb form should be in range [0, 255]\n");
	}
	r = ft_atoi_rtv(coords[0]);
	g = ft_atoi_rtv(coords[1]);
	b = ft_atoi_rtv(coords[2]);
	ft_free_char_arr(&coords);
	if (r > 255 || g > 255 || b > 255)
		parse_error(p, rt, value,
			"color in rgb form should be in range [0, 255]\n");
	object->color = ((r << 16) | (g << 8) | b);
}

void		parse_obj_color(char *value, t_parse *p, t_object *object, t_rt *rt)
{
	char	*cmp;

	cmp = NULL;
	if (*value == '[')
	{
		parse_obj_color_rgb(value, p, object, rt);
		return ;
	}
	if (*value == '"')
	{
		cmp = ft_strndup(value + 1, ft_strlen(value) - 2);
		if (*cmp == '-')
			parse_error(p, rt, value, "color should be non-negative\n");
		object->color = ft_atoi_hex(cmp);
		ft_strdel(&cmp);
	}
	else if (*value == '-')
		parse_error(p, rt, value, "color should be non-negative\n");
	else
		object->color = ft_atoi_rtv(value);
	if (object->color < 0)
		parse_error(p, rt, value, "color should be in [0; INT_MAX]\n");
}
