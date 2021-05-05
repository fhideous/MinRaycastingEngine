NAME	   = cub3D

SRCS	   =  main.c parser_map.c get_next_line.c get_next_line_utils.c \
                            parse_set.c find_player.c create_win.c stuff.c \
                            parser_map_stuff.c ray.c \
                            mlx_commands.c screan.c messages.c map_validate.c all_free.c parse_color.c \
                            movements.c to_window.c sprite_preparation.c big_kek.c
OBJS	   =  ${SRCS:.c=.o}

MLX	       =  mlx

LIBFT		= lib

FLAGS	   = -Wall -Wextra

CC         = gcc

$(NAME):     $(OBJS)
	$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT)
	$(CC) -O3 -o $(NAME) $(OBJS) -L$(MLX) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT) -lft

%.o: %.c
	$(CC) -O3 $(FLAGS)  -c $< -o $@

all:        $(NAME)

clean:
			rm -f ${OBJS}
			rm -f ${BONUS_OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f screenshot.bmp
			$(MAKE) -C $(LIBFT) fclean
			$(MAKE) -C $(MLX) clean

re:			fclean all

.PHONY:		all bonus clean fclean re