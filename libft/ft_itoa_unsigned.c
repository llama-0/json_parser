#include "libft.h"

char	*ft_itoa_unsigned(long long n)
{
	char		*integer;
	int			len;
	long long	tmp;

	len = 1;
	if (n == (LLMIN))
		return (ft_strdup(LLMAX));
	if (n < 0)
		n *= -1;
	tmp = n;
	while ((tmp = tmp / 10))
		len++;
	if (!(integer = (char *)malloc(len + 1)))
		return (NULL);
	integer[len] = '\0';
	while (len--)
	{
		integer[len] = n % 10 + '0';
		n /= 10;
	}
	return (integer);
}
