#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line;
	(void)ac;
	(void)av;
	
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		printf("Teste: %s\n", line);
		add_history(line);
		exec_line(line, envp);
		free(line);
	}
	return (0);
}