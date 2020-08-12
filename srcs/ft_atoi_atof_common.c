#include "libparse.h"

void		skip_spaces_and_sign(const char *str, size_t *i, int *sign)
{
	*i = 0;
	*sign = 0;
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '-')
		*sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
}

void		process_e(char *e, double *res)
{
	int sign;
	int pow;

	sign = 0;
	pow = ft_atoi_base_check(++e);
	if (pow < 0)
	{
		sign = 1;
		pow = -pow;
	}
	while (pow > 0)
	{
		if (sign)
			*res /= 10;
		else
			*res *= 10;
		pow--;
	}
}
