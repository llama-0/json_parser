#include "libparse.h"

static void		comma_not_null(char *content, char *comma,
								size_t *len, t_dict **head)
{
	char	*elem;

	elem = NULL;
	if (*len == 0)
	{
		elem = ft_strndup(content, comma - content);
		(*len)--;
	}
	else
		elem = ft_strndup(content + *len + 1, (comma - content) - *len - 1);
	push_back_pair(head, new_pair(elem));
	*len += ft_strlen(elem) + 1;
	ft_strdel(&elem);
}

static void		parse_last_elem(char *content, t_dict **head, size_t len)
{
	char	*elem;
	char	*comma;

	elem = NULL;
	comma = ft_strrchr(content, ',');
	elem = ft_strndup(content + len + 1, (comma - content) - len - 1);
	push_back_pair(head, new_pair(elem));
	ft_strdel(&elem);
}

static t_dict	*last_is_array(char *content, size_t len,
								size_t j, t_dict **head)
{
	char	*elem;
	char	*comma;

	comma = NULL;
	elem = NULL;
	comma = ft_strnchr(content, ',', j -= 3);
	elem = ft_strndup(content + len + 1, (comma - content) - len - 1);
	push_back_pair(head, new_pair(elem));
	ft_strdel(&elem);
	return (*head);
}

t_dict			*number_of_args(char *content)
{
	t_dict	*head;
	char	*comma;
	size_t	len;
	size_t	j;

	head = NULL;
	len = 0;
	j = 1;
	while (content[len] != '\0')
	{
		if ((comma = ft_strnchr(content, ',', j)) && *(comma + 1) != '"')
		{
			if ((comma = ft_strnchr(content, ',', j += 2)) == NULL)
				return (last_is_array(content, len, j, &head));
		}
		if (comma)
			comma_not_null(content, comma, &len, &head);
		else
			break ;
		j++;
	}
	if (len < ft_strlen(content))
		parse_last_elem(content, &head, len);
	return (head);
}
