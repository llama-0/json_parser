#include "libparse.h"

static void		ft_fractional(const char *s, size_t *i, double *res)
{
	size_t		k;
	int			depth;

	(*i)++;
	k = 1;
	depth = 0;
	while (s[*i] != '\0' && s[*i] >= '0' && s[*i] <= '9' && depth++ < 7)
	{
		if (depth == JSON_PRECI + 1)
		{
			if (s[*i] > '4')
				*res = *res + 0.000001;
			break ;
		}
		else
			*res = *res + (s[(*i)++] - '0') / ft_pow(10, k++);
	}
}

static double	ft_atof_base_check(const char *str)
{
	size_t	i;
	double	res;
	int		sign;

	res = 0.0;
	skip_spaces_and_sign(str, &i, &sign);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((int)res >= 1000)
			return (sign == 1 ? -1000 : 1000);
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		ft_fractional(str, &i, &res);
	if (sign)
		return (-res);
	return (res);
}

double			ft_atof_rtv(const char *str)
{
	char	*e;
	char	*tmp;
	double	res;

	res = 0.0;
	e = ft_strchr(str, 'e');
	if (e == NULL)
		e = ft_strchr(str, 'E');
	if (e != NULL)
	{
		tmp = ft_strndup(str, e - str + 1);
		res = ft_atof_base_check(tmp);
		ft_strdel(&tmp);
		if (res != 0.0 && *(e + 1) != '\0')
			process_e(e, &res);
	}
	else
		res = ft_atof_base_check(str);
	return (res);
}
