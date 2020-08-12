NAME = parse

LIBPARSE_NAME = libparse.a

DEBUG = -g

WFLAGS = -Wall -Wextra -Werror

YELLOW = \x1B[33m
GREEN = \x1B[32m
BLUE = \x1B[34m
RESET = \x1B[0m

LIBFT_DIR = libft
SRC_DIR = srcs
MAIN_SRC_DIR = srcs/test

SRCS = dict.c \
		dict_find.c \
		vec3_for_parse.c \
		ft_atoi_atof_common.c \
		ft_atoi_rtv.c \
		ft_atof_rtv.c \
		ft_ftoa_rtv.c \
		ft_check_range.c \
		validation_step_one.c \
		validation_base_loop.c \
		validate_json.c \
		clear_outer_keys.c \
		parse_error.c \
		number_of_args.c \
		general_functions.c \
		parse_camera.c \
		parse_required_obj_fields.c \
		parse_other_obj_fields.c \
		parse_advanced_obj_fields.c \
		parse_sliced_obj_fields.c \
		objects_balancer.c \
		parse_objects.c \
		parse_required_light_fields.c \
		parse_lights.c \
		objects.c \
		lights.c \
		keys.c \
		parse_json.c \

MAIN = main.c \
		print_funcs.c

LIBFT = -L $(LIBFT_DIR) -lft
LIBPARSE = -L. -lparse

OBJ_DIR = objs
MAIN_OBJ_DIR = $(MAIN_SRC_DIR)/objs_main

SRC = $(addprefix $(SRC_DIR)/, $(SRCS))

MAIN_SRC = $(addprefix $(MAIN_SRC_DIR), $(MAIN))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MAIN_OBJ = $(addprefix $(MAIN_OBJ_DIR)/, $(MAIN:.c=.o))

INCLUDES = -I includes -I $(LIBFT_DIR)/includes

HDR = includes/libparse.h $(LIBFT_DIR)/includes/libft.h

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(LIBPARSE_NAME)
	make -C $(LIBFT_DIR)
	@gcc $(DEBUG) $(WFLAGS) -o $(NAME) $(INCLUDES) $(MAIN_OBJ) $(LIBFT) $(LIBPARSE)
	@echo "$(GREEN)json_parser is ready$(RESET)"
	@echo "$(YELLOW)**********************************$(RESET)"
	@echo "$(YELLOW)** ./parse json_scenes/10.json **$(RESET)"
	@echo "$(YELLOW)**********************************$(RESET)"

$(LIBPARSE_NAME): $(OBJ)
	ar rc $(LIBPARSE_NAME) $(OBJ)
	ranlib $(LIBPARSE_NAME)
	@echo "$(GREEN)libparse.a is ready$(RESET)"

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	gcc $(DEGUB) $(WFLAGS) $(INCLUDES) -c $< -o $@

$(MAIN_OBJ): $(MAIN_OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/%.c $(HDR)
	@mkdir -p $(MAIN_OBJ_DIR)
	gcc $(DEGUB) $(WFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(MAIN_OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	@echo "$(BLUE)Object files removed$(RESET)"

fclean: clean
	rm -f $(LIBPARSE_NAME)
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "$(BLUE)Binary files removed$(RESET)"

re: fclean all

.PHONY: all re fclean clean
