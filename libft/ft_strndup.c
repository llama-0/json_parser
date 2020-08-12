#include "libft.h"

char	*ft_strndup(const char *s1, unsigned char n)
{
	int		i;
	char	*s2;

	i = 0;
	if (!(s2 = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (n != 0 && s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
		n--;
	}
	s2[i] = '\0';
	return (s2);
}
