#include "libft.h"

int	ft_atoi_hex(char *s)
{
	int	i;
	int	res;

	if (s[0] != '0' || s[1] != 'x')
		return (0);
	s += 2;
	i = 0;
	res = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 1)
			res = res * 16 + s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			res = res * 16 + s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			res = res * 16 + s[i] - 'A' + 10;
		i++;
	}
	if (res <= 0x7FFFFFFF && res >= 0)
		return (res);
	return (-1);
}
