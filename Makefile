NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-lreadline

SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	.
LIBFT_DIR	=	$(SRC_DIR)/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SOURCES		=	$(SRC_DIR)/core/main.c \
				$(SRC_DIR)/core/signals.c \
				$(SRC_DIR)/parsing/parsing.c \
				$(SRC_DIR)/parsing/parsing_tokenize.c \
				$(SRC_DIR)/parsing/parsing_tokenize_ops.c \
				$(SRC_DIR)/parsing/parsing_cmd.c \
				$(SRC_DIR)/parsing/parsing_redir.c \
				$(SRC_DIR)/parsing/parsing_parse.c \
				$(SRC_DIR)/execution/execution.c \
				$(SRC_DIR)/execution/execution_exec.c \
				$(SRC_DIR)/execution/execution_path.c \
				$(SRC_DIR)/execution/execution_pipes.c \
				$(SRC_DIR)/execution/execution_redir.c \
				$(SRC_DIR)/builtins/builtins_main.c \
				$(SRC_DIR)/builtins/builtins_misc.c \
				$(SRC_DIR)/builtins/builtins_export.c \
				$(SRC_DIR)/builtins/builtins_unset.c \
				$(SRC_DIR)/builtins/builtins_dispatch.c \
				$(SRC_DIR)/env/environment.c \
				$(SRC_DIR)/env/environment_set.c \
				$(SRC_DIR)/utils/utils_memory.c \
				$(SRC_DIR)/utils/utils_expand.c \
				$(SRC_DIR)/utils/utils_expand_helpers.c \
				$(SRC_DIR)/utils/utils_expand_process.c \
				$(SRC_DIR)/utils/utils_quotes.c

OBJECTS		=	$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
