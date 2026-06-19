/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:26:47 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 18:12:55 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TYPES_H
# define MS_TYPES_H

# define MAX_TOKENS 1024
# define MAX_TOKEN_LEN 8192

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	int				argc;
	t_redir			*redirects;
	int				pipe_in;
	int				pipe_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char			**envp;
	int				exit_status;
	char			*current_path;
	char			**paths;
	int				pipe_fd[2];
	int				last_pipe_out;	pid_t		pid;	t_token			*tokens;
	t_cmd			*commands;
}	t_shell;

typedef struct s_reader
{
	char	*res;
	size_t	len;
	size_t	cap;
}	t_reader;

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_REDIR_APPEND 4
# define TOKEN_HEREDOC 5
# define TOKEN_AND 6
# define TOKEN_OR 7
# define TOKEN_PAREN_OPEN 8
# define TOKEN_PAREN_CLOSE 9
# define TOKEN_SEMICOLON 10

# define REDIR_IN 0
# define REDIR_OUT 1
# define REDIR_APPEND 2
# define REDIR_HEREDOC 3

#endif
