#include "libparse.h"
// #include "libsdl.h"

void	json_parse_error(char *message, char *s)
{
	write(2, JSON_PARSER_ERROR_PROMPT, ft_strlen(JSON_PARSER_ERROR_PROMPT));
	write(2, message, ft_strlen(message));
	ft_strdel(&s);
	// sdl_memory(NULL);
	exit(1);
}

void	parse_error(t_parse *p, t_rt *rt, char *optional, char *msg)
{
	ft_strdel(&optional);
	ft_strdel(&p->content);
	ft_free_rt(rt);
	json_parse_error(msg, p->s);
}

void	parse_error_basic(char *optional, t_rt *rt, char *s, char *msg)
{
	ft_strdel(&optional);
	ft_free_rt(rt);
	json_parse_error(msg, s);
}

void	ft_free_rt(t_rt *rt)
{
	ft_free_light_list(&rt->light);
	ft_free_obj_list(&rt->object);
	ft_free_key_list(&rt->key);
	free(rt);
	rt = NULL;
}
