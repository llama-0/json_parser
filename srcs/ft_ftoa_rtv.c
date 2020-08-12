#include "libparse.h"

/*
** convert first <precision + 1> digits of fraction part to ascii
*/

static char	*ft_fract(long double fract, int preci)
{
	char		*f;
	int			len;

	if (!(f = ft_strnew(preci + 1)))
		return (NULL);
	len = -1;
	while (++len < preci + 1)
	{
		fract *= 10;
		if (preci % 2 != 0 && preci > 9 && len == preci)
			f[len] = (long long)fract % 10 - 1 + '0';
		else
			f[len] = (long long)fract % 10 + '0';
	}
	return (f);
}

/*
** shift number to the right if there happens extra '1'
*/

static void	ft_shift(char *f)
{
	char	a;
	char	b;

	a = '1';
	while (*f)
	{
		b = *f;
		*f = a;
		a = b;
		f++;
	}
	*(f - 1) = '0';
}

/*
** apply rounding to double, modified by koparker for rtv
*/

static void	ft_fract_end(char *f, int size)
{
	if (size == -1)
	{
		ft_shift(f);
		return ;
	}
	else if (f[size + 1] < '5')
		f[size + 1] = 0;
	else
	{
		if (f[size] < '9')
		{
			f[size] += 1;
			f[size + 1] = 0;
		}
	}
}

/*
** convert long double to ascii, modified by koparker for rtv
*/

char		*ft_ftoa_rtv(long double fparam, int preci)
{
	long long	intgr;
	char		*f;
	char		*tmp;
	int			ilen;

	intgr = (long long)fparam;
	if (!(tmp = ft_itoa_unsigned(intgr)))
		return (NULL);
	ilen = ft_strlen(tmp) + 1;
	if (!(f = ft_strnew(ilen + preci + 1)))
		ft_strdel(&tmp);
	ft_strcat(f, tmp);
	ft_strcat(f, ".");
	ft_strdel(&tmp);
	if (!(tmp = ft_fract(fparam - (long long)fparam, preci)))
		ft_strdel(&f);
	ft_strcat(f + ilen, tmp);
	ft_strdel(&tmp);
	ft_fract_end(f, ilen + preci - 1);
	return (f);
}
