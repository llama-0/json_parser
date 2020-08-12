#include "libft.h"

double	ft_pow(int n, int pow)
{
	double	res;

	res = 1;
	while (pow-- > 0)
		res *= n;
	return (res);
}
