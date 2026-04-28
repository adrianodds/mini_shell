/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmoliv <carmoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:50:21 by carmoliv          #+#    #+#             */
/*   Updated: 2026/04/28 17:54:25 by carmoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_line_blank(const char *line)
{
	size_t	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static char	*read_interactive_line(void)
{
	return (readline("minishell$ "));
}

char	*read_shell_input(void)
{
	if (isatty(STDIN_FILENO))
		return (read_interactive_line());
	return (read_line_from_fd(STDIN_FILENO));
}

static void	exec_input(t_shell *shell, char *input)
{
	parse_input(shell, input);
	if (shell->commands)
		execute_commands(shell, shell->commands);
	free_commands(shell->commands);
	shell->commands = NULL;
}

void	handle_input(t_shell *shell, char *input)
{
	size_t	len;

	if (isatty(STDIN_FILENO) && *input && !is_line_blank(input))
		add_history(input);
	if (*input == '\n')
		return ;
	len = ft_strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	if (!is_line_blank(input))
		exec_input(shell, input);
}
