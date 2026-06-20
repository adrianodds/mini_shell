# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/20 15:48:08 by adduarte          #+#    #+#              #
#    Updated: 2026/06/20 16:59:14 by adduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-lreadline

SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	.
LIBFT_DIR	=	$(SRC_DIR)/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

VALGRIND_SUPP	=	valgrind_suppression.supp

SOURCES		=	$(SRC_DIR)/core/main.c \
				$(SRC_DIR)/core/read_fd.c \
				$(SRC_DIR)/core/read_fd_utils.c \
				$(SRC_DIR)/core/input.c \
				$(SRC_DIR)/core/signals.c \
				$(SRC_DIR)/parsing/parsing.c \
				$(SRC_DIR)/parsing/heredoc.c \
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
				$(SRC_DIR)/builtins/help_builtin_cd.c \
				$(SRC_DIR)/builtins/print_export.c \
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

$(VALGRIND_SUPP):
	@echo "{" > $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:readline" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:add_history" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:_rl_*" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_keymap_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:rl_make_bare_keymap" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_keymap_suppression2" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:rl_generic_bind" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   suppress_execve_bin_error" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   obj:/usr/bin/*" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)

v: $(NAME) $(VALGRIND_SUPP)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./$(VALGRIND_SUPP) ./$(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(VALGRIND_SUPP)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re v