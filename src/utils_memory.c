#include "../minishell.h"

char	**split_str(char *str, char *delim)
{
	char	**result;
	int		count;
	int		i;
	char	*copy;
	char	*token;

	count = 0;
	copy = ft_strdup(str);
	token = strtok(copy, delim);
	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	free(copy);
	result = malloc(sizeof(char *) * (count + 1));
	copy = ft_strdup(str);
	i = 0;
	token = strtok(copy, delim);
	while (token)
	{
		result[i++] = ft_strdup(token);
		token = strtok(NULL, delim);
	}
	result[i] = NULL;
	free(copy);
	return (result);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;
	t_redir	*redir;
	t_redir	*next_redir;
	int		i;

	current = commands;
	while (current)
	{
		next = current->next;
		i = 0;
		while (current->args[i])
			free(current->args[i++]);
		free(current->args);
		redir = current->redirects;
		while (redir)
		{
			next_redir = redir->next;
			free(redir->file);
			free(redir);
			redir = next_redir;
		}
		free(current);
		current = next;
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	free(shell->envp);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->commands)
		free_commands(shell->commands);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
