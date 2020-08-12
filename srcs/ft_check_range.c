#include "libparse.h"

static int	fractional_not_empty(int fractional, size_t preci)
{
	while (preci != 0)
	{
		if (fractional % 10 != 0)
			return (1);
		fractional /= 10;
		preci--;
	}
	return (0);
}

static int	check_result(int fractional, int inclusive)
{
	int	not_empty;

	not_empty = fractional_not_empty(fractional, JSON_PRECI);
	if (not_empty && inclusive)
		return (0);
	if (not_empty && !inclusive)
		return (1);
	if (!not_empty && !inclusive)
		return (0);
	return (1);
}

/*
** checks double to be in range [0..1] or (1..2) or (0..1]
*/

int			ft_check_range(double n, int inclusive)
{
	char	*nbr;
	char	*fract;
	int		integer;
	int		fractional;
	int		i;

	nbr = NULL;
	fract = NULL;
	integer = (int)n;
	nbr = ft_ftoa_rtv(n, JSON_PRECI);
	i = 0;
	while (nbr[i] != '.')
		i++;
	fract = ft_strdup(nbr + i + 1);
	ft_strdel(&nbr);
	fractional = ft_atoi(fract);
	ft_strdel(&fract);
	if (integer == 1)
		return (check_result(fractional, inclusive));
	else if (integer > 1 || (integer < 1
				&& fractional_not_empty(fractional, JSON_PRECI)
				&& !inclusive))
		return (0);
	return (1);
}
