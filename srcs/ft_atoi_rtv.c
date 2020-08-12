#include "libparse.h"

int	ft_atoi_base_check(const char *str)
{
	size_t	i;
	long	res;
	int		sign;

	res = 0;
	skip_spaces_and_sign(str, &i, &sign);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((res = res * 10 + str[i++] - '0') < 0)
		{
			if (i - 1 == ft_strlen(str))
				break ;
			return (-1);
		}
	}
	if (sign)
		return ((int)(-res));
	return ((int)res);
}

int	ft_atoi_rtv(const char *str)
{
	char	*e;
	char	*tmp;
	double	tmp_e;
	int		res;

	res = 0;
	e = ft_strchr(str, 'e');
	if (e == NULL)
		e = ft_strchr(str, 'E');
	if (e != NULL)
	{
		tmp = ft_strndup(str, e - str + 1);
		res = ft_atoi_base_check(tmp);
		ft_strdel(&tmp);
		if (res != 0.0 && *(e + 1) != '\0')
		{
			tmp_e = res;
			process_e(e, &tmp_e);
			res = tmp_e;
		}
	}
	else
		res = ft_atoi_base_check(str);
	return (res);
}
