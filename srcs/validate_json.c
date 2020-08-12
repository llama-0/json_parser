#include "libparse.h"

static int	coords_false(char *tmp, char **str)
{
	ft_strdel(&tmp);
	ft_free_char_arr(&str);
	return (0);
}

static int	is_coords_valid(char buf[VAL_BUFF_SIZE],
								size_t *i, size_t j, size_t k)
{
	size_t	r;
	char	*tmp;
	char	**str;

	tmp = ft_strndup(buf + 1, k - 1);
	r = 0;
	while (tmp[r] != '\0' && ft_strchr(JSON_COORDS_FORBIDDEN, tmp[r]) == NULL)
	{
		if (tmp[r] == '.' && (r == 0 || (r != 0
								&& (tmp[r - 1] == ',' || tmp[r - 1] == '-'))
							|| r + 1 == ft_strlen(tmp)
							|| (r + 1 < ft_strlen(tmp)
								&& (tmp[r + 1] == '.' || tmp[r + 1] == ','))))
			return (coords_false(tmp, NULL));
		r++;
	}
	if (tmp[r] != '\0')
		return (coords_false(tmp, NULL));
	str = ft_strsplit(tmp, ',');
	if (ft_2d_strlen(str) != 3 || ft_strchr(tmp, '"') != NULL)
		return (coords_false(tmp, str));
	*i = j;
	ft_free_char_arr(&str);
	ft_strdel(&tmp);
	return (1);
}

int			is_coords_array_form(char *s, size_t *i, size_t len)
{
	size_t	j;
	size_t	k;
	char	buf[VAL_BUFF_SIZE];

	(void)len;
	j = *i + 1;
	k = 0;
	ft_bzero(buf, VAL_BUFF_SIZE);
	while (s[j] != ']')
	{
		if (!ft_isspace(s[j]))
			buf[k++] = s[j];
		j++;
	}
	if (s[j + 1] == ',' || s[j + 1] == '}')
	{
		return (is_coords_valid(buf, i, j, k));
	}
	return (0);
}

char		*check_json_validity(char *s)
{
	char	*src;

	src = read_file_strip_ws(s);
	if (!check_validity(src))
	{
		ft_strdel(&src);
		json_parse_error("invalid syntax\n", src);
	}
	return (src);
}
