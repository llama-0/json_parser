#include "libparse.h"

static void	fill_obj(t_object **node, t_object object)
{
	(*node)->id = object.id;
	(*node)->type = object.type;
	(*node)->center = object.center;
	(*node)->normal = object.normal;
	(*node)->radius = object.radius;
	(*node)->torus_radius = object.torus_radius;
	(*node)->angle = object.angle;
	(*node)->color = object.color;
	(*node)->specular = object.specular;
	(*node)->translation = object.translation;
	(*node)->rotation = object.rotation;
	(*node)->reflective = object.reflective;
	(*node)->transparancy = object.transparancy;
	(*node)->transparancy_percent = object.transparancy_percent;
	(*node)->sliced = object.sliced;
	(*node)->sliced_up = object.sliced_up;
	(*node)->len_up = object.len_up;
	(*node)->len_down = object.len_down;
	(*node)->negative = object.negative;
}

t_object	*new_obj(t_object object)
{
	t_object	*node;

	if (!(node = (t_object *)ft_memalloc(sizeof(t_object))))
	{
		ft_putendl_fd("malloc for object failed", 2);
		return (NULL);
	}
	fill_obj(&node, object);
	node->next = NULL;
	return (node);
}

void		push_back_obj(t_object **head, t_object *node)
{
	t_object	*tmp;

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

size_t		ft_obj_list_size(t_object *lst)
{
	t_object	*tmp;
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

void		ft_free_obj_list(t_object **head)
{
	t_object	*tmp;

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
