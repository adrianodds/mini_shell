#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	int				last_pipe_out;
	t_token			*tokens;
	t_cmd			*commands;
}	t_shell;

/* Token types */
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

/* Redirection types */
# define REDIR_IN 0
# define REDIR_OUT 1
# define REDIR_APPEND 2
# define REDIR_HEREDOC 3

/* Function prototypes */

/* Main functions */
void			minishell_loop(t_shell *shell);

/* Parsing functions */
void			parse_input(t_shell *shell, char *input);
t_token			*tokenize(t_shell *shell, char *input);
t_cmd			*parse_tokens(t_shell *shell, t_token *tokens);
void			parse_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens);

/* Execution functions */
void			execute_commands(t_shell *shell, t_cmd *commands);
void			execute_single_cmd(t_shell *shell, t_cmd *cmd);
void			handle_builtin(t_shell *shell, t_cmd *cmd);
int				is_builtin(const char *cmd);

/* Builtin commands */
int				builtin_echo(t_shell *shell, t_cmd *cmd);
int				builtin_cd(t_shell *shell, t_cmd *cmd);
int				builtin_pwd(t_shell *shell, t_cmd *cmd);
int				builtin_export(t_shell *shell, t_cmd *cmd);
int				builtin_unset(t_shell *shell, t_cmd *cmd);
int				builtin_env(t_shell *shell, t_cmd *cmd);
int				builtin_exit(t_shell *shell, t_cmd *cmd);

/* Environment functions */
char			*get_env(t_shell *shell, const char *key);
void			set_env(t_shell *shell, const char *key, const char *value);
char			**copy_envp(char **envp);
char			*expand_variables(t_shell *shell, const char *str);
char			*remove_quotes(const char *str);
int				ft_isalnum(int c);
char			*ft_itoa(int n);

/* Pipe and redirection */
void			setup_pipes(t_shell *shell, t_cmd *cmd);
void			close_pipes(t_shell *shell, t_cmd *commands);
void			handle_redirections(t_shell *shell, t_cmd *cmd);

/* Signal handling */
void			setup_signals(void);
void			handle_sigint(int sig);

/* Utility functions */
char			**split_str(char *str, char *delim);
void			free_tokens(t_token *tokens);
void			free_commands(t_cmd *commands);
void			free_shell(t_shell *shell);
void			free_split(char **split);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strcat(char *dest, const char *src);
void			add_token(t_token **tokens, char *value, int len, int type);

#endif
