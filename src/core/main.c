/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:50:27 by carmoliv          #+#    #+#             */
/*   Updated: 2026/06/19 18:19:29 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_signal = 0;

static void	setup_signals(void);
static void	setup_readline(void);
static void	minishell_loop(t_shell *shell);
static void	exec_input(t_shell *shell, char *input);

static void	exec_input(t_shell *shell, char *input)
{
	parse_input(shell, input);
	if (shell->commands)
		execute_commands(shell, shell->commands);
	free_commands(shell->commands);
	shell->commands = NULL;
}

static void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = read_shell_input();
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				write(1, "exit\n", 5);
			break ;
		}
		handle_input(shell, input);
		free(input);
	}
}

static void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	setup_readline(void)
{
	rl_clear_history();
	rl_on_new_line();
	rl_bind_keyseq("\\033[5~", rl_get_previous_history);
	rl_bind_keyseq("\\033[6~", rl_get_next_history);
	rl_completion_query_items = 256;
	rl_completion_entry_function = rl_filename_completion_function;
	rl_bind_key('\t', rl_complete);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.envp = copy_envp(envp);
	shell.exit_status = 0;
	shell.current_path = get_env(&shell, "PWD");
	shell.tokens = NULL;
	shell.commands = NULL;
	shell.last_pipe_out = -1;
	shell.pid = getpid();
	setup_signals();
	setup_readline();
	if (argc > 2 && ft_strncmp(argv[1], "-c", 3) == 0)
		exec_input(&shell, argv[2]);
	else
		minishell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}
