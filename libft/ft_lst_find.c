#include "libft.h"

t_list	*ft_lst_find(t_list **lst, char *value)
{
	t_list	*tmp;

	if (!lst || !(*lst) || !value)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->content, value) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
