#include "libparse.h"

t_key	*new_key(char *content)
{
	t_key	*node;

	if (!(node = (t_key *)ft_memalloc(sizeof(t_key))))
	{
		ft_putendl_fd("malloc for key failed", 2);
		return (NULL);
	}
	node->content = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	add_key(t_key **alst, t_key *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

size_t	ft_key_list_size(t_key *lst)
{
	t_key	*tmp;
	size_t	i;

	i = 0;
	tmp = lst;
	if (lst == NULL)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_free_key_list(t_key **head)
{
	t_key	*tmp;

	if (*head == NULL)
		return ;
	tmp = NULL;
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

t_key	*ft_key_find(t_key **lst, char *value)
{
	t_key	*tmp;

	if (!lst || !(*lst) || !value)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->content, value) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
