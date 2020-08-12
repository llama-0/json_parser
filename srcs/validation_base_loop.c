#include "libparse.h"

/*
** skip letters that are not a part of json syntax building blocks
** which is --> ":{[,]}
*/

static void	skip_other_letters(char *s, size_t *i)
{
	while (s[*i] != '\0' && ft_strchr(JSON_ALPHABET, s[*i]) == NULL)
		(*i)++;
}

static int	is_match(char tmp, char s)
{
	if ((s == ']' && tmp == '[')
		|| (s == '}' && tmp == '{')
		|| (s == '"' && tmp == '"'))
		return (1);
	return (0);
}

static int	is_comma_or_colon(char *s, size_t *i, size_t len)
{
	if (s[*i] == ',' && (*i + 1) < len
							&& ((s[*i - 1] == '"' && s[*i + 1] == '"')
							|| (ft_isdigit(s[*i - 1]) && s[*i + 1] == '"')
							|| (s[*i - 1] == '}' && s[*i + 1] == '{')
							|| (s[*i - 1] == ']' && s[*i + 1] == '"')
							|| (s[*i - 1] == '}' && s[*i + 1] == '"')))
		return (1);
	if (s[*i] == ':' && s[*i - 1] == '"'
					&& (*i + 1) < len && s[*i + 1] == '['
					&& (*i + 2) < len && s[*i + 2] != '{')
		return (is_coords_array_form(s, i, len));
	if (s[*i] == ':' && (*i + 1) < len && s[*i - 1] == '"'
							&& (ft_isdigit(s[*i + 1])
							|| s[*i + 1] == '['
							|| s[*i + 1] == '{'
							|| s[*i + 1] == '"'
							|| (s[*i + 1] == '-'
							&& (*i + 2) < len && ft_isdigit(s[*i + 2]))))
		return (1);
	return (0);
}

static int	validity_inner_check(char *s, size_t *i, size_t *j, char *tmp)
{
	size_t	len;

	len = ft_strlen(s);
	if (*i < len)
	{
		if (tmp[0] != '\0' && is_match(tmp[*j - 1], s[*i]))
			tmp[--(*j)] = '\0';
		else if (s[*i] == ',' || s[*i] == ':')
		{
			if (!is_comma_or_colon(s, i, len))
				return (0);
		}
		else
			tmp[(*j)++] = s[*i];
	}
	return (1);
}

int			check_validity(char *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*tmp;

	i = 0;
	if (i == 0 && s[i] != '{')
		return (0);
	j = 0;
	len = ft_strlen(s);
	tmp = ft_memalloc(len);
	while (i < len)
	{
		skip_other_letters(s, &i);
		if (validity_inner_check(s, &i, &j, tmp))
			i++;
		else
			break ;
	}
	ft_strdel(&tmp);
	if (j == 0)
		return (1);
	return (0);
}
