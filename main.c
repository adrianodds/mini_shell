#include "minishell.h"

// Signal handler global — necessário para o SIGINT
static volatile sig_atomic_t	g_signal = 0;
volatile sig_atomic_t	g_exit_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);	// CTRL+C → nova linha de prompt
	signal(SIGQUIT, SIG_IGN);		// CTRL+\ → ignorar no prompt
}

char	**duplicate_envp(char **envp)
{
	int		count;
	char	**copy;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			copy[i] = NULL;
			free_args(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;

	(void)ac;
	(void)av;
	env = duplicate_envp(envp);
	if (!env)
		return (1);
	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);	// CTRL+D — comportamento do bash
			break ;
		}
		if (*line)					// só adiciona ao histórico se não for linha vazia
			add_history(line);
		exec_line(line, &env);
		free(line);
	}
	free_args(env);
	return (0);
}