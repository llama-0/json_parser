#include "libparse.h"

t_lights	*new_light(t_lights light)
{
	t_lights	*node;

	if (!(node = (t_lights *)ft_memalloc(sizeof(t_lights))))
	{
		ft_putendl_fd("malloc for light failed", 2);
		return (NULL);
	}
	node->type = light.type;
	node->position = light.position;
	node->intensity = light.intensity;
	node->next = NULL;
	return (node);
}

void		push_back_light(t_lights **head, t_lights *node)
{
	t_lights	*tmp;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

size_t		ft_light_list_size(t_lights *lst)
{
	t_lights	*tmp;
	size_t		i;

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

void		ft_free_light_list(t_lights **head)
{
	t_lights *tmp;

	if (*head == NULL)
		return ;
	tmp = NULL;
	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}
