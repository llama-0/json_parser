#include "libparse.h"

size_t	key_present(t_dict **head, char *key)
{
	t_dict	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** determine if duplicate keys present in a dictionary
*/

size_t	has_duplicates(t_dict **head)
{
	t_dict	*dict;
	t_list	*lst;

	lst = NULL;
	dict = *head;
	while (dict != NULL)
	{
		if (ft_lst_find(&lst, dict->key) != NULL)
		{
			ft_lstdel(&lst, ft_lstfree_node);
			return (1);
		}
		else
			ft_lstadd(&lst, ft_lstnew(dict->key, ft_strlen(dict->key)));
		dict = dict->next;
	}
	ft_lstdel(&lst, ft_lstfree_node);
	return (0);
}

char	*get_dict_value(t_dict **head, char *key)
{
	t_dict	*tmp;

	if (!head || !(*head) || !key)
		return (NULL);
	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_dict(t_dict **head)
{
	t_dict	*dict;

	dict = *head;
	while (dict)
	{
		ft_putstr_fd(dict->key, 1);
		ft_putchar('+');
		ft_putendl_fd(dict->value, 1);
		dict = dict->next;
	}
}

size_t	ft_dict_size(t_dict *dict)
{
	t_dict	*tmp;
	size_t	i;

	i = 0;
	tmp = dict;
	if (dict == NULL)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
