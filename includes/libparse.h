#ifndef LIBPARSE_H
# define LIBPARSE_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>

/*
** validation
*/

# define VAL_BUFF_SIZE 128
# define JSON_ALPHABET "\":{[,]}"
# define JSON_COORDS_FORBIDDEN "\"'+:{[]}"

/*
** json_parser
*/

# define JSON_LIGHTS "lights"
# define JSON_OBJECTS "objects"
# define JSON_CAMERA "camera"

# define JSON_PARSER_ERROR_PROMPT "json_parser: Error: "
# define KEY_DUPLICATES "outer key duplicates are forbidden\n"
# define JSON_FILE_ERROR_MSG "Make adjustments to BUFF_SIZE in "
# define JSON_FILE_ERROR_PATH "srcs/libft/includes/libft.h"
# define JSON_FILE_ERROR JSON_FILE_ERROR_MSG JSON_FILE_ERROR_PATH

/*
** precision is now hidden deep inside the code,
** but exposed here on top of things among defines
*/

# define JSON_PRECI 6

# define PI 180
# define PI_OVER_TWO 90
# define COORDS_LEN 3
# define EPS 1e6
# define MAX_INT 2147483647

# define HEX_WHITE 0xffffff

typedef struct	s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}				t_dict;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_camera
{
	t_vec3	look_at;
	t_vec3	position;
}				t_camera;

typedef enum	e_light_type
{
	ambient,
	dot,
	directional,
	nonexistent
}				t_light_type;

typedef struct	s_lights
{
	struct s_lights	*next;
	int				id;
	t_light_type	type;
	t_vec3			position;
	double			intensity;
}				t_lights;

typedef enum	e_shape
{
	plane,
	sphere,
	cylinder,
	cone,
	torus,
	none
}				t_shape;

typedef struct	s_parse
{
	char	*content;
	char	*s;
	t_dict	*head;
	size_t	fl_intensity;
	size_t	fl_position;
	size_t	fl_look_at;
	size_t	fl_center;
	size_t	fl_normal;
	size_t	fl_radius;
	size_t	fl_torus_radius;
	size_t	fl_angle;
	size_t	fl_sliced_up;
	size_t	fl_len_up;
	size_t	fl_len_down;
}				t_parse;

typedef struct	s_key
{
	struct s_key	*next;
	char			*content;
}				t_key;

/*
** At parse angle value equals the input value from .json
** When all checks performed, angle transforms into tangent of angle
** (needed in cone intersection formula)
*/

typedef struct	s_object
{
	struct s_object	*next;
	int				id;
	t_shape			type;
	t_vec3			center;
	t_vec3			normal;
	double			radius;
	double			torus_radius;
	double			angle;
	int				color;
	int				specular;
	t_vec3			translation;
	t_vec3			rotation;
	double			reflective;
	double			transparancy;
	double			transparancy_percent;
	unsigned char	sliced;
	t_vec3			sliced_up;
	double			len_up;
	double			len_down;
	unsigned char	negative;
}				t_object;

typedef struct	s_rt
{
	t_object		*object;
	t_lights		*light;
	t_key			*key;
	t_camera		camera;
}				t_rt;

/*
** DICTIONARY
*/

t_dict			*new_pair(char *s);
void			push_back_pair(t_dict **head, t_dict *elem);
size_t			key_present(t_dict **head, char *key);
void			dict_clear(t_dict **head);
void			print_dict(t_dict **head);
size_t			ft_dict_size(t_dict *dict);
char			*get_dict_value(t_dict **head, char *key);
size_t			has_duplicates(t_dict **head);

/*
** vec3 implementation (only creation and length needed for parcing)
*/

t_vec3			vec3(double x, double y, double z);
double			v3_length(t_vec3 v);

void			init_camera(t_camera *c);

/*
** json validator
*/

char			*read_file_strip_ws(char *file_name);
int				is_coords_array_form(char *s, size_t *i, size_t len);
int				check_validity(char *s);
char			*check_json_validity(char *s);

/*
** json parser
*/

void			ft_clear_light(t_lights *light);
void			ft_clear_camera(t_camera *camera);
void			ft_clear_object(t_object *object);

void			parse_error_basic(char *optional, t_rt *rt, char *s, char *msg);
void			parse_error(t_parse *p, t_rt *rt, char *optional, char *msg);

void			required_obj_fields_check(t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_center(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_normal(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_radius(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_torus_radius(char *value, t_parse *p,
													t_object *object, t_rt *rt);

void			parse_obj_angle(char *value, t_parse *p, t_object *object,
																	t_rt *rt);

void			parse_obj_type(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_translation(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_rotation(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_specular(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_color(char *value, t_parse *p, t_object *object,
																	t_rt *rt);

void			parse_obj_reflective(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_transparency(char *value, t_parse *p,
													t_object *object, t_rt *rt);
void			parse_obj_transparency_percent(char *value, t_parse *p,
													t_object *object, t_rt *rt);
void			parse_obj_negative(char *value, t_parse *p, t_object *object,
																	t_rt *rt);

void			parse_obj_sliced_up(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_len_up(char *value, t_parse *p, t_object *object,
																	t_rt *rt);
void			parse_obj_len_down(char *value, t_parse *p, t_object *object,
																	t_rt *rt);

void			required_light_fields_check(t_parse *p, t_lights *light,
																	t_rt *rt);
void			parse_light_intensity(char *value, t_parse *p, t_lights *light,
																	t_rt *rt);

void			init_parse(t_parse *p, char *content, t_dict *head, char *s);
void			check_value_form(char *value, t_parse *p, t_rt *rt);
char			**parse_coords(char *value, t_rt *rt, t_parse *p);
char			*get_content(char bracket, char *s, size_t *i, size_t j);

void			object_values_required(char *value, t_parse *p,
												t_object *object, t_rt *rt);
void			other_object_values(char *value, t_parse *p,
												t_object *object, t_rt *rt);
void			advanced_object_values(char *value, t_parse *p,
												t_object *object, t_rt *rt);
void			sliced_object_values(char *value, t_parse *p,
												t_object *object, t_rt *rt);

void			parse_json(char *s, t_rt *rt);
void			json_parse_error(char *message, char *s);
t_dict			*number_of_args(char *content);

void			check_value_form(char *value, t_parse *p, t_rt *rt);
void			parse_camera(t_rt *rt, size_t *i, size_t j, char *s);
void			parse_objects(t_rt *rt, size_t *i, size_t j, char *s);
void			parse_lights(t_rt *rt, size_t *i, size_t j, char *s);

void			ft_free_rt(t_rt *rt);
t_dict			*check_dict_values(char *content, t_rt *rt, char *s);
void			skip_spaces_and_sign(const char *str, size_t *i, int *sign);
int				ft_atoi_base_check(const char *str);
void			process_e(char *e, double *res);
int				ft_atoi_rtv(const char *str);
double			ft_atof_rtv(const char *str);
char			*ft_ftoa_rtv(long double fparam, int preci);
int				ft_check_range(double n, int inclusive);

/*
** objects
*/

t_object		*new_obj(t_object object);
void			push_back_obj(t_object **head, t_object *node);
size_t			ft_obj_list_size(t_object *lst);
void			ft_free_obj_list(t_object **head);

/*
** lights
*/

t_lights		*new_light(t_lights light);
void			push_back_light(t_lights **head, t_lights *node);
size_t			ft_light_list_size(t_lights *lst);
void			ft_free_light_list(t_lights **head);

/*
** keys (outer keys: camera, lights, objects)
*/

t_key			*new_key(char *content);
size_t			ft_key_list_size(t_key *lst);
void			ft_free_key_list(t_key **head);
t_key			*ft_key_find(t_key **lst, char *value);
void			add_key(t_key **alst, t_key *new);

#endif
