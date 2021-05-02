NAME	   = cub3D

SRCS	   = ./main.c ./parser_map.c ./gnl/get_next_line.c\
                     ./parse_set.c ./find_player.c ./create_win.c ./stuff.c\
                     ./scene_put.c ./ray.c\
                     ./mlx_commands.c ./screan.c


OBJS	   =  ${SRCS:.c=.o}

LIBFT_DIR	= lib/

GNL_DIR		= gnl/

MLX_DIR    = mlx_mac/

MLX	       =  mlx_mac

MLX_A		= mlx_mac/libmlx.a

MLXFLAGS    = -framework OpenGL -framework Appkit

INCLUDES    = -I${LIBFT_DIR} -I${GNL_DIR} -I${GNL_DIR}

LIBFT		= lib

FLAGS	   = -fsanitize=address

CC         = gcc

CFLAGS      = -fsanitize=address

$(NAME):     $(OBJS)
	$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT)
	${CC} ${CFLAGS} ${OBJS} ${INCLUDES} -L${LIBFT} -lft -L${MLX} ${MLX_A} ${MLXFLAGS} -o ${NAME}

%.o: %.c
	$(CC) $(FLAGS)  ${INCLUDES} -c $< -o ${<:.c=.o}

all:        $(NAME)

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f screenshot.bmp
			$(MAKE) -C $(LIBFT) fclean
			$(MAKE) -C $(MLX) clean

re:			fclean all

.PHONY:		all clean fclean re
