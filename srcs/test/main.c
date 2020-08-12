#include "libparse.h"
#include "time.h"
#include <stdio.h>

void		print_key_list(t_key **head);
void		print_light_list(t_lights **head);
void		print_object_list(t_object **head);
void		v3_print(t_vec3 v);

static void	print_parsed_rt_contents(t_rt *rt)
{
	t_rt	*tmp;

	tmp = rt;
	print_key_list(&rt->key);
	print_light_list(&rt->light);
	print_object_list(&rt->object);
	printf("camera position: ");
	v3_print(rt->camera.position);
	printf("camera look_at: ");
	v3_print(rt->camera.look_at);
}

static void init_main_struct(t_rt **rt)
{
    if (!(*rt = (t_rt *)malloc(sizeof(t_rt))))
        ft_putendl_fd("OOPS! struct t_rt failed to malloc", 2);
    ft_bzero(*rt, sizeof(t_rt));
}

int			main(int ac, char **av)
{
	t_rt	*rt;
	char	*s;
	clock_t time;

	if (ac != 2)
		ft_putendl_fd("usage: ./parse json_scene_file]", 2);
	time = clock();
	s = check_json_validity(av[1]);
	init_main_struct(&rt);
	parse_json(s, rt);
	ft_strdel(&s);
	printf("validation & parse done in %f\n", (double)(clock() - time) / CLOCKS_PER_SEC);
	print_parsed_rt_contents(rt);
	ft_free_key_list(&rt->key);
	ft_free_rt(rt);
	return (0);
}
