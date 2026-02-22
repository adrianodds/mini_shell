NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes -I libft/includes

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c exec.c utils.c path.c builtins.c validation_identifier.c built_export.c built_unset.c


OBJS = $(SRC:.c=.o)

all:	$(NAME)
$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	
fclean:	clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re:	fclean all


.PHONY:	all clean fclean re