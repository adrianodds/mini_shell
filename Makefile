NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes -I libft/includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRC = main.c exec.c utils.c path.c builtins.c


OBJS = $(SRC:.c=.o)

all:	$(NAME)
$(NAME):	$(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(PRINTF) -lreadline -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	$(RM) $(OBJS)
	
fclean:	clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	$(RM) $(NAME)

re:	fclean all


.PHONY:	all clean fclean re