NAME =		rtv1

SRCS = 		srcs/main.c srcs/objects.c srcs/raytracer.c srcs/parser.c \
			srcs/get_cam.c srcs/get_sphere.c srcs/lst.c

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
