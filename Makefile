NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-lreadline

SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	.

SOURCES		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/parsing.c \
				$(SRC_DIR)/execution.c \
				$(SRC_DIR)/builtins.c \
				$(SRC_DIR)/environment.c \
				$(SRC_DIR)/utils.c

OBJECTS		=	$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
