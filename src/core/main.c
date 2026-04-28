/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adduarte <adduarte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:14:52 by adduarte          #+#    #+#             */
/*   Updated: 2026/04/28 16:13:16 by adduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_signal = 0;

static void	minishell_loop(t_shell *shell);
static void	setup_readline(void);
static int	handle_tab(int count, int key);

static char	*read_shell_input(void)
{
	char	*input;
	size_t	len;

	if (isatty(STDIN_FILENO))
		return (readline("minishell$ "));
	write(STDOUT_FILENO, "minishell$ \n", 12);
	input = NULL;
	len = 0;
	if (getline(&input, &len, stdin) == -1)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

static void	handle_input(t_shell *shell, char *input)
{
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
}

static void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	setup_readline(void)
{
	rl_bind_key('\t', handle_tab);
}

static int	handle_tab(int count, int key)
{
	int	i;

	(void)count;
	(void)key;
	if (!rl_line_buffer)
		return (rl_insert(1, '\t'));
	i = 0;
	while (rl_line_buffer[i] == ' ' || rl_line_buffer[i] == '\t')
		i++;
	if (rl_line_buffer[i] == '\0')
		return (rl_insert(1, '\t'));
	if (rl_point == 0)
		return (rl_insert(1, '\t'));
	if (rl_line_buffer[rl_point - 1] == ' '
		|| rl_line_buffer[rl_point - 1] == '\t')
		return (rl_possible_completions(1, '\t'));
	return (rl_complete(1, '\t'));
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
	setup_signals();
	setup_readline();
	if (argc > 2 && ft_strncmp(argv[1], "-c", 3) == 0)
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

static void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = read_shell_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_input(shell, input);
		free(input);
	}
}
