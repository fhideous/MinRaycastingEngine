NAME	   = cub3D

SRCS	   = main.c main_utils.c main_ray.c parser1.c\
	parser2.c parser3.c parser_extras.c get_next_line.c\
	config.c keyinput.c closeandforget.c sprites.c screenshot.c

OBJS	   =  ${SRCS:.c=.o}

BONUS_OBJS =  ${BONUS_SRCS:.c=.o}

MLX	       =  mlxlinux

LIBFT		= libft

FLAGS	   = -Wall -Wextra -Werror -g

CC         = gcc

$(NAME):     $(OBJS)
	$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT)
	$(CC)   -o $(NAME) $(OBJS)  -L$(MLX) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT) -lft

bonus:  	fclean $(BONUS_OBJS)
	$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT)
	$(CC)   -o $(NAME) $(BONUS_OBJS)  -L$(MLX) -lmlx -lXext -lX11 -lm -lz -L$(LIBFT) -lft

%.o: %.c
	$(CC) $(FLAGS)  -c $< -o $@

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
