#include "../minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.envp = copy_envp(envp);
	shell.exit_status = 0;
	shell.current_path = get_env(&shell, "PWD");
	shell.tokens = NULL;
	shell.commands = NULL;
	shell.last_pipe_out = -1;
	setup_signals();
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		parse_input(&shell, argv[2]);
		if (shell.commands)
			execute_commands(&shell, shell.commands);
		free_commands(shell.commands);
		shell.commands = NULL;
	}
	else
		minishell_loop(&shell);
	free_shell(&shell);
	return (shell.exit_status);
}

void	minishell_loop(t_shell *shell)
{
	char	*input;
	size_t	len;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline("minishell$ ");
		else
		{
			printf("minishell$ \n");
			fflush(stdout);
			input = NULL;
			len = 0;
			if (getline(&input, &len, stdin) == -1)
				break ;
		}
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (isatty(STDIN_FILENO) && *input)
			add_history(input);
		if (*input != '\n')
		{
			if (input[ft_strlen(input) - 1] == '\n')
				input[ft_strlen(input) - 1] = '\0';
			parse_input(shell, input);
			if (shell->commands)
				execute_commands(shell, shell->commands);
			free_commands(shell->commands);
			shell->commands = NULL;
		}
		free(input);
		fflush(stdout);
		fflush(stderr);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
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
