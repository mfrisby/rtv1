NAME =		rtv1

SRCS = 		srcs/main.c srcs/raytracer.c  srcs/raytracelight.c\
			srcs/calcul_objects.c srcs/while_objects.c \
			srcs/lst.c srcs/utils.c srcs/free_heads.c\
			srcs/parser.c srcs/get_cam.c srcs/get_sphere.c srcs/get_plan.c \
			srcs/get_cylindre.c srcs/get_cone.c srcs/get_light.c\
			srcs/get_colision.c \

INCLUDES = 	-I ./inc

MLX =  -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

LIBFT = ./libft/libft.a

OBJS = $(patsubst srcs/%.c, objs/%.o, $(SRCS))

FLAGS =	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): 	objs $(OBJS)
			@make -C libft/
			@gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
			@echo "\033[32mCompilation OK\033[m"

objs/%.o: 	srcs/%.c
			@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

objs:
			@mkdir -p objs

clean:
	@rm -rf objs
	@echo "\033[33mclean done\033[m"

fclean: 		clean
	@/bin/rm -f $(NAME)
	@echo "\033[33mfclean done\033[m"

libfc:
	@make -C libft/ fclean

re: 			fclean all

.PHONY = 		all clean fclean re
