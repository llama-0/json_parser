#include "libparse.h"

static void	make_pair(char *s, t_dict **elem)
{
	char	*tmp;
	size_t	len;

	if ((tmp = ft_strchr(s, ':')) != NULL)
	{
		(*elem)->key = ft_strndup(s + 1, tmp - s - 2);
		len = ft_strlen((*elem)->key);
		if (*(tmp + 1) != '\0')
			(*elem)->value = ft_strndup(s + len + 3,
					ft_strlen(s) - len - 1);
		else
			(*elem)->value = ft_strdup("");
	}
	else
	{
		(*elem)->key = ft_strdup("");
		(*elem)->value = ft_strdup("");
	}
}

t_dict		*new_pair(char *s)
{
	t_dict	*elem;
	char	*tmp;

	if (!(elem = (t_dict *)ft_memalloc(sizeof(t_dict))))
	{
		ft_putendl_fd("malloc failed for new_pair", 2);
		return (NULL);
	}
	make_pair(s, &elem);
	elem->next = NULL;
	tmp = NULL;
	return (elem);
}

void		push_back_pair(t_dict **head, t_dict *elem)
{
	t_dict	*tmp;

	if (*head == NULL)
	{
		*head = elem;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = elem;
}

t_dict		*check_dict_values(char *content, t_rt *rt, char *s)
{
	t_dict	*head;
	t_dict	*tmp;

	head = number_of_args(content);
	tmp = head;
	while (tmp)
	{
		if (ft_strequ(tmp->value, ""))
		{
			tmp = NULL;
			dict_clear(&head);
			parse_error_basic(content, rt, s, "empty values are forbidden\n");
		}
		tmp = tmp->next;
	}
	return (head);
}

void		dict_clear(t_dict **head)
{
	t_dict	*tmp;

	tmp = NULL;
	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		free(tmp);
		tmp = NULL;
	}
	*head = NULL;
}
