#include "../../minishell.h"

extern int	g_signal;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
