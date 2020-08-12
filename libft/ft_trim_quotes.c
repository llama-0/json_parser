#include "libft.h"

char	*ft_trim_quotes(char const *s, char quote)
{
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	ft_putendl_fd(s, 1);
	if (s[0] == quote && s[n - 1] == quote)
		return (ft_strndup(s + 1, n - 2));
	return (NULL);
}
