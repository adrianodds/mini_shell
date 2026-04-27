#include "../../minishell.h"

void	parse_input(t_shell *shell, char *input)
{
	shell->tokens = tokenize(shell, input);
	if (!shell->tokens)
		return ;
	shell->commands = parse_tokens(shell, shell->tokens);
}
