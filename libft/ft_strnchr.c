#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			count++;
		if (count == n)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
