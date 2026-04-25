#include "../minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.envp = copy_envp(envp);
	shell.exit_status = 0;
	shell.current_path = get_env(&shell, "PWD");
	shell.tokens = NULL;
	shell.commands = NULL;
	setup_signals();
	minishell_loop(&shell);
	free_shell(&shell);
	return (0);
}

void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		parse_input(shell, input);
		if (shell->commands)
			execute_commands(shell, shell->commands);
		free_commands(shell->commands);
		shell->commands = NULL;
		free(input);
		fflush(stdout);
		fflush(stderr);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
